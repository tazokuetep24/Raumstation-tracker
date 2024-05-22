#include "satellite_window.h"
#include "ui_satellite.h"
#include "api.h"
#include "uart.h"
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtGlobal>
#include <QStyle>
#include <QApplication>


/**
 * @brief Constructor of the class Satellite
 *
 * Initialise and configure buttons
 *
 */
Satellite::Satellite(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Satellite)
    , limitIsReached(false)
    , trackIsPressed(false)
{
    ui->setupUi(this);
    ui->altLabel->setText("ELEVATION:");

    // Create and configure stop button
    stop = new QPushButton("Stop Tracking", this);
    stop->setFont(QFont("Arial", 13));
    stop->setFixedSize(150, 50);
    stop->move(100, 485);
    connect(stop, &QPushButton::clicked, this, &Satellite::onStopClicked);
    stop->setEnabled(false);

    // Create and configure goback button
    goback = new QPushButton("Go back to initial position", this);
    goback->setFont(QFont("Arial", 11));
    goback->setFixedSize(200, 50);
    goback->move(530, 485);
    connect(goback, &QPushButton::clicked, this, &Satellite::onGoBackClicked);
    goback->setEnabled(false);

    // Hide buttons first
    ui->buttonBox->setVisible(false);

    // Open Serial Port
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM3");
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort, &QSerialPort::readyRead, this, &Satellite::handleSerialData);
}

/**
 * @brief Default Destructor of the class Satellite
 *
 */
Satellite::~Satellite()
{
    serialPort->close();
    delete serialPort;
    delete ui;
}

/**
 * @brief Handles the button click event for tracking the satellite position.
 *
 * This function is called when the user clicks the "Track" button in the Satellite window.
 * It initiates the satellite tracking process, enabling the "Stop" and "Go Back" buttons.
 *
 * @see Satellite::on_stopBtn_clicked()
 * @see Satellite::on_gobackBtn_clicked()
 */
void Satellite::on_trackBtn_clicked()
{
    // Set tracking Flag to true
    trackIsPressed = true;

    // Enable stop and go back buttons
    stop->setEnabled(true);
    goback->setEnabled(true);
}
/**
 * @brief Handles incoming serial data from the connected STM32 board.
 *
 * This function is triggered whenever there is incoming data on the serial port.
 * It reads the received data, prints it to the console, and checks for specific
 * messages indicating limit conditions reached by the X or Y motor. If a limit is reached,
 * an error dialog is displayed to inform the user about the motor limit condition.
 *
 * @note The function assumes that the received data format is a string indicating the
 * status of the motors (e.g., "0" for X-Motor limit, "1" for Y-Motor limit, other values for general errors).
 *
 * @see Satellite::sendPosition(double deltaAz, double deltaElv)
 * @see Satellite::on_trackBtn_clicked()
 * @see Satellite::on_stopBtn_clicked()
 * @see Satellite::on_gobackBtn_clicked()
 *
 * @note The function sets the 'limitIsReached' flag to true after handling the data.
 */
void Satellite::handleSerialData()
{
    QByteArray data = serialPort->readAll();

    // Print received data and any errors to the console
    qDebug() << "Received data:" << data;
    if (serialPort->error() != QSerialPort::NoError)
    {
        qDebug() << "Serial port error:" << serialPort->errorString();
    }

    // X Motor has reached limit
    if (data == "0")
    {
        // When sendig fails, display an error dialog
        showErrorDialog("Limit reached", "X-Motor has reached limit!");
    }
    // X Motor has reached limit
    else if (data == "1"){
        showErrorDialog("Limit reached", "Y-Motor has reached limit!");
    }
    else {
        showErrorDialog("Limit reached", "Motor has reached limit!");
    }
    //limitIsReached = true;
}
/**
 * @brief Handles the "Stop" button click event.
 *
 * This function is triggered when the user clicks the "Stop" button in the satellite control window.
 * It logs a message to the console, sets the 'limitIsReached' flag to true and sends the value
 * "999.999" to the connected STM32 board indicating a stop position.
 *
 * @note The function is designed to stop the motors
 *
 * @see Satellite::handleSerialData()
 * @see Satellite::sendPosition(double deltaAz, double deltaElv)
 * @see Satellite::on_trackBtn_clicked()
 * @see Satellite::on_gobackBtn_clicked()
 *
 */
void Satellite::onStopClicked()
{
    qDebug() << "Stop clicked!";
    limitIsReached = true;
    serialPort->close();
    delay(500);
    /* The position 999.999 999.999 is sent requesting a stop*/
    sendPosition(999.999, 999.999);
    serialPort->open(QIODevice::ReadWrite);
}
/**
 * @brief Handles the "Go Back to initial position" button click event.
 *
 * This function is triggered when the user clicks the "Go Back to initial position" button in the satellite control window.
 * It logs a message to the console, sets the 'limitIsReached' flag to true and sends the value
 * "888.8888 8888.8888 " to the connected STM32 board to go back to start position.
 *
 * @note The function is designed reset motors position
 *
 * @see Satellite::handleSerialData()
 * @see Satellite::sendPosition(double deltaAz, double deltaElv)
 * @see Satellite::on_trackBtn_clicked()
 * @see Satellite::on_gobackBtn_clicked()
 *
 */
void Satellite::onGoBackClicked()
{
    qDebug() << "Go Back clicked!";
    limitIsReached = true;
    serialPort->close();
    delay(500);
    sendPosition(888.888, 888.888);
    serialPort->open(QIODevice::ReadWrite);
}
/**
 * @brief Updates the LCD displays with satellite position information.
 *
 * This function is responsible for updating the LCD displays in the satellite control window with the
 * current satellite position information. It takes the 'currentPosition' as a parameter and uses it to
 * access the relevant data from the 'positions' array. The function updates the Latitude, Longitude,
 * Elevation, and Azimuth values displayed on the LCD screens.
 *
 * @param currentPosition The index representing the current position in the 'positions' array.
 *
 *
 * @see Satellite::on_trackBtn_clicked()
 * @see Satellite::getSatellitePosition(int noradId, double observerLat, double observerLng,
 *                                       double observerAlt, int seconds, const QString& apiKey,
 *                                       satPos positions[MAX_REQUEST])
 */
void Satellite::updateLCD(int currentPosition)
{
    // Display Satellite Latitude
    ui->latLCD->display(positions[currentPosition].satlatitude);
    // Display Satellite Longitude
    ui->longLCD->display(positions[currentPosition].satlongitude);
    // Display Satellite Elevation
    ui->altLCD->display(positions[currentPosition].elevation);
    // Display Satellite Azimuth
    ui->azmLCD->display(positions[currentPosition].azimuth);
}
/**
 * @brief Initiates satellite tracking and updates the UI with real-time position data.
 *
 * This function starts the satellite tracking loop, continuously updating the UI with real-time
 * position data. It initializes variables for tracking, loads satellite positions, and enters a
 * loop that updates the UI, checks for significant changes in satellite position, and controls
 * the satellite tracking behavior by sending position differences to the STM32 board.
 *
 * @note If a difference greater than or equal to 3.6 in the satellite position at any component
 *       (azimuth or elevation) is detected, the position difference is sent to the STM32 board
 *       to move the motors accordingly.
 *
 * @see Satellite::getSatellitePosition(int noradId, double observerLat, double observerLng,
 *                                       double observerAlt, int seconds, const QString& apiKey,
 *                                       satPos positions[MAX_REQUEST])
 * @see Satellite::updateLCD(int currentPosition)
 * @see Satellite::sendPosition(double deltaAz, double deltaElv)
 *
 * @note The function will display an error dialog if loading satellite positions fails.
 *       The tracking loop continues until the satellite control window is closed.
 */
void Satellite::start(){

    limitIsReached = false;

    // Load satellite position (300 positions advance)
    bool gotSatPos = getSatellitePosition(satID, MY_LATITUDE, MY_LONGITUDE,
                                          MY_ALTITUDE, MAX_REQUEST, API_KEY, positions);

    // If loading satellite positions failed, display an error dialog
    if (!gotSatPos){
        // Display Error Dialog
        showErrorDialog("Error API","Cannot Load Sattelite Positoins!" );
        return;
    }

    // Initialise variables
    double currAz = 0.0;
    double currElv = 0.0;
    double prevAz = 00; //90
    double prevElv = 00;
    double deltaAz = 0.0;
    double deltaElv = 0.0;
    int currentPosition = 0;

    while(this->isVisible()){
        // Reached last loaded position
        if (currentPosition == MAX_REQUEST - 1)
        {
            // Load Data again (new API request)
            getSatellitePosition(satID, MY_LATITUDE, MY_LONGITUDE,
                                 MY_ALTITUDE, MAX_REQUEST, API_KEY, positions);
            currentPosition = 0;
        }

        // Update LCD
        updateLCD(currentPosition);
        // Get current azimuth and elevation
        currAz = positions[currentPosition].azimuth;
        currElv = positions[currentPosition].elevation;
        // Calculate azimuth and elevation difference from the last postion
        deltaAz = currAz - prevAz;
        deltaElv = currElv - prevElv;

        // If a difference greater than or equal to 3.6 in the satellite position,
        // send position difference over UART
        if (abs(deltaAz) >= 1.8 || abs(deltaElv) >= 1.8){
            if (trackIsPressed && !limitIsReached){  ///< Tracking and motor limit not reached yet
                serialPort->close();
                if(!sendPosition(deltaAz, deltaElv)){
                    // When sendig fails, display an error dialog
                    showErrorDialog("Error STM32", "Cannot connect to the STM32 board!\n"
                                                   "Please make sure that the board is connected to the right COM port");
                }
                serialPort->open(QIODevice::ReadWrite);
                if (abs(deltaAz) >= 1.8){
                    prevAz = positions[currentPosition].azimuth;
                }
                if (abs(deltaElv) >= 1.8){
                    prevElv = positions[currentPosition].elevation;
                }

            }
        }
        // Go to next positon and delay for 1s
        currentPosition++;
        delay(1000);
    }
}
/**
 * @brief Handles the close event for the satellite control window.
 *
 * This function is called when the user attempts to close the satellite control window.
 * It signals the tracking loop to stop by setting 'limitIsReached' to 'true' and accepts the close event.
 *
 * @param event A pointer to the close event.
 *
 * @see Satellite::start()
 */
void Satellite::closeEvent(QCloseEvent *event){
    limitIsReached = true;
    event->accept();
}
/**
 * @brief showErrorDialog
 */
void Satellite::showErrorDialog(QString title, QString message){
    // Create a custom QMessageBox
    QMessageBox messageBox;

    // Set the window icon
    messageBox.setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));

    // Set the title and text
    messageBox.setWindowTitle(title);
    messageBox.setText(message);

    // Set the icon for the QMessageBox (using the Critical role for an error)
    messageBox.setIconPixmap(QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical).pixmap(32, 32)); // You can adjust the size

    // Add an "OK" button
    messageBox.setStandardButtons(QMessageBox::Ok);

    // Show the custom QMessageBox
    messageBox.exec();
}
