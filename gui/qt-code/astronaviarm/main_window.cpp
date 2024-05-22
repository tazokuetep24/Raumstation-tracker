#include "main_window.h"
#include "ui_astronaviarm.h"
#include "satellite_window.h"
#include "ui_satellite_window.h"
#include <QPixmap>
#include <QIcon>
#include <QProgressDialog>
#include <QTimer>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include <QMessageBox>


/**
 * @brief Default constructor of the class AstroNaviArm
 */
AstroNaviArm::AstroNaviArm(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AstroNaviArm), satWindow(nullptr)
{
    ui->setupUi(this);

    // Set the  window size
    setFixedSize(800, 600);

    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));

    // Load the logo pixmap
    QPixmap logoPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/logo.png");

    // Get the size of the label
    QSize logoLabelSize = ui->logoLabel->size();

    // Scale the pixmap to the size of the label
    ui->logoLabel->setPixmap(logoPix.scaled(logoLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Load the Robot pixmap
    QPixmap robotPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/robot_photo2.png");
    // Get the size of the label
    QSize robotLabelSize = ui->robotLabel->size();
    // Scale the pixmap to the size of the label
    ui->robotLabel->setPixmap(robotPix.scaled(robotLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->tiangong_btn->setText("Galileo 27 Satellite");

    connect(ui->tiangong_btn, &QPushButton::clicked, this, &AstroNaviArm::onTiangongButtonClicked);
    connect(ui->starlink_btn, &QPushButton::clicked, this, &AstroNaviArm::onStarlinkButtonClicked);
}
/**
 * @brief Default destructor of the class AstroNaviArm
 */
AstroNaviArm::~AstroNaviArm()
{
    delete ui;
    delete satWindow;
}
/**
 * @brief Handles the button click event to track the International Space Station (ISS).
 *
 * This function is called when the user clicks the button to track the ISS. It creates a new instance
 * of the Satellite window, sets its properties such as title, icon, and image, and then shows the window.
 * The window's tracking loop is started, which continuously updates the position of the ISS and sends
 * relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::on_iss_btn_clicked()
{
    // Create Satellite Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("ISS");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = "International Space Station \n \t (ISS)";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap ISSPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/iss.png");
    // Get the size of the photoLabel
    QSize ISSLabelSize = satWindow->ui->photoLabel->size();
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(ISSPix.scaled(ISSLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set satellite ID
    int ID = 25544;         // ID of ISS
    satWindow->satID = ID;

    // Show Window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Handles the button click event to track the Hubble Space Telescope.
 *
 * This function is called when the user clicks the button to track the Hubble Space Telescope (Hublle).
 * It creates a new instance of the Satellite window, sets its properties such as title, icon, and image,
 * and then shows the window. The window's tracking loop is started, which continuously updates the
 * position of the Hubble Space Telescope and sends relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::on_huble_btn_clicked()
{
    // Create Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("Hublle");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = "  Hubble Space Telescope \n";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap HubllePix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/hublle.png");
    // Get the size of the photoLabel
    QSize HublleLabelSize = satWindow->ui->photoLabel->size();
    satWindow->ui->photoLabel->move(390, satWindow->ui->photoLabel->y());
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(HubllePix.scaled(HublleLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set satellite ID
    int ID = 20580;     // ID of Hublle
    satWindow->satID = ID;

    // Strat Window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Handles the button click event to track the NOAA 15 Weather Satellite.
 *
 * This function is called when the user clicks the button to track the NOAA 15 Weather Satellite.
 * It creates a new instance of the Satellite window, sets its properties such as title, icon, and image,
 * and then shows the window. The window's tracking loop is started, which continuously updates the
 * position of the NOAA 15 satellite and sends relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::on_noaa_btn_clicked()
{
    // Create Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("NOAA 15");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = "  NOAA15 Weather Satellite \n";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap NOAAPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/noaa.png");
    // Get the size of the photoLabel
    QSize NOAALabelSize = satWindow->ui->photoLabel->size();
    satWindow->ui->photoLabel->move(370, satWindow->ui->photoLabel->y());
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(NOAAPix.scaled(NOAALabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set satellite Id
    int ID = 25338;     // ID of NOAA
    satWindow->satID = ID;


    // Start Window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Handles the button click event to track the Iridium 1 Communication Satellite.
 *
 * This function is called when the user clicks the button to track the NOAA 15 Weather Satellite.
 * It creates a new instance of the Satellite window, sets its properties such as title, icon, and image,
 * and then shows the window. The window's tracking loop is started, which continuously updates the
 * position of the NOAA 15 satellite and sends relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::on_iridium_btn_clicked()
{
    // Create Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("Iridium 1");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = " Iridium 1 Communication Satellite \n";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap IridiumPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/iridium.png");
    // Get the size of the photoLabel
    QSize IridiumLabelSize = satWindow->ui->photoLabel->size();
    satWindow->ui->photoLabel->move(430, satWindow->ui->photoLabel->y() - 20);
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(IridiumPix.scaled(IridiumLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set satellite ID
    int ID = 56730;     // ID of iridium
    satWindow->satID = ID;

    // Start Window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Handles the button click event to track the GOES 13 Weather Satellite.
 *
 * This function is called when the user clicks the button to track the NOAA 15 Weather Satellite.
 * It creates a new instance of the Satellite window, sets its properties such as title, icon, and image,
 * and then shows the window. The window's tracking loop is started, which continuously updates the
 * position of the NOAA 15 satellite and sends relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::on_goes_btn_clicked()
{
    // Create Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("GOES 13");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = "  GOES 13 Weather Satellite \n";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap GOESPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/goes.png");
    // Get the size of the photoLabel
    QSize GOESLabelSize = satWindow->ui->photoLabel->size();
    satWindow->ui->photoLabel->move(370, satWindow->ui->photoLabel->y());
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(GOESPix.scaled(GOESLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set satellite ID
    int ID = 29155;     // ID of GOES
    satWindow->satID = ID;

    // Start window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Handles the button click event to track the Galileo 27 Satellite.
 *
 * This function is called when the user clicks the button to track the NOAA 15 Weather Satellite.
 * It creates a new instance of the Satellite window, sets its properties such as title, icon, and image,
 * and then shows the window. The window's tracking loop is started, which continuously updates the
 * position of the NOAA 15 satellite and sends relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::onTiangongButtonClicked(){
    // Create Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("Galileo 27");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = "  Galileo 27 Satellite \n";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap GalileoPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/galileo.png");
    // Get the size of the photoLabel
    QSize GalileoLabelSize = satWindow->ui->photoLabel->size();
    satWindow->ui->photoLabel->move(370, satWindow->ui->photoLabel->y());
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(GalileoPix.scaled(GalileoLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set Satellite ID
    int ID = 49809;  // ID of Galileo 27
    satWindow->satID = ID;

    // Start Window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Handles the button click event to track the Starlink 30401 Satellite.
 *
 * This function is called when the user clicks the button to track the NOAA 15 Weather Satellite.
 * It creates a new instance of the Satellite window, sets its properties such as title, icon, and image,
 * and then shows the window. The window's tracking loop is started, which continuously updates the
 * position of the NOAA 15 satellite and sends relevant data to control the motors.
 *
 * @see Satellite
 * @see Satellite::start()
 */
void AstroNaviArm::onStarlinkButtonClicked(){
    // Create Window
    satWindow = new Satellite(this);
    // Set Window Title
    satWindow->setWindowTitle("Starlink-30401");
    // Set the window icon
    setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));
    // Set Title
    const QString title = "  Starlink 30401 Satellite \n";
    satWindow->ui->titleLabel->setText(title);
    satWindow->ui->titleLabel->setAlignment(Qt::AlignCenter);
    // Load the Robot pixmap
    QPixmap GalileoPix("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/starlink.png");
    // Get the size of the photoLabel
    QSize GalileoLabelSize = satWindow->ui->photoLabel->size();
    satWindow->ui->photoLabel->move(420, satWindow->ui->photoLabel->y());
    // Scale the pixmap to the size of the label
    satWindow->ui->photoLabel->setPixmap(GalileoPix.scaled(GalileoLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set satellite ID
    int ID = 57818; // ID of Starlink-30401
    satWindow->satID = ID;

    // Start Window
    showLoadingBox();
    satWindow->show();
    satWindow->start();
}
/**
 * @brief Displays a loading dialog to simulate the process of loading satellite position data.
 *
 * This function creates and shows a QProgressDialog, providing visual feedback to the user
 * that the application is retrieving satellite position data. The dialog includes a progress bar
 * that updates over a simulated 3-second process.
 */
void AstroNaviArm::showLoadingBox()
{
    // Create a QProgressDialog
    QProgressDialog progressDialog("Loading Satellite Position. Please Wait...", "Cancel", 0, 100);
    progressDialog.setWindowTitle("Getting Satellite Data");
    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.setWindowIcon(QIcon("C:/Users/cheba/my-projects/qt-projects/AstroNaviArm/photos/icon.png"));

    // Set up a timer to simulate a 3-second process
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        // Update the progress bar
        progressDialog.setValue(progressDialog.value() + 1);

        // Check if the progress is complete
        if (progressDialog.value() == progressDialog.maximum()) {
            progressDialog.close();
            qDebug() << "Loading complete!";
            QCoreApplication::quit();
        }
    });

    // Start the timer to update the progress every 20 milliseconds
    timer.start(20);

    // Show the progress dialog
    progressDialog.exec();
}
