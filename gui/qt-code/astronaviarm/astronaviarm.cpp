#include "astronaviarm.h"
#include "ui_astronaviarm.h"
#include "satellite.h"
#include "ui_satellite.h"
#include "r_w_data.h"
#include <QPixmap>
#include <QIcon>
#include <QProgressDialog>
#include <QTimer>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>



AstroNaviArm::AstroNaviArm(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AstroNaviArm), satWindow(nullptr)
{
    ui->setupUi(this);

    // Set the desired window size
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

}

AstroNaviArm::~AstroNaviArm()
{
    delete ui;
    delete satWindow;
}

void AstroNaviArm::on_iss_btn_clicked()
{
    if (!satWindow) {
        satWindow = new Satellite(this);  // Set the parent to AstroNaviArm
        connect(satWindow, &QDialog::finished, this, [this](int result) {
            // Handle the window closed event if needed
            // You can perform actions when the Satellite window is closed
            satWindow = nullptr;  // Reset the pointer after the window is closed
        });
    }

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

    // ID of ISS
    int ID = 25544;
    satWindow->satID = ID;


    satPos positions[MAX_REQUEST];

    bool gotSatPos = getSatellitePosition(ID, MY_LATITUDE, MY_LONGITUDE, MY_ALTITUDE, MAX_REQUEST, API_KEY, positions);

    showLoadingBox();
    delay(1000);

    if (gotSatPos)
    {
        satWindow->show();
    }
    else
    {
        qDebug() << " Error Loading Satellite Data";
    }

    int currentIdx = 0;
    while(1)
    {
        // If we reach last position, load new positions
        if (currentIdx == MAX_REQUEST - 1)
        {
            bool gotSatPos = getSatellitePosition(ID, MY_LATITUDE, MY_LONGITUDE, MY_ALTITUDE, MAX_REQUEST, API_KEY, positions);
            if (!gotSatPos)
            {
                qDebug() << "Error Loading Data";
                break;
            }
        }

        // Display Satellite Latitude
        satWindow->ui->latLCD->display(positions[currentIdx].satlatitude);

        // Display Satellite Longitude
        satWindow->ui->longLCD->display(positions[currentIdx].satlongitude);

        // Display Satellite Altitude
        satWindow->ui->altLCD->display(positions[currentIdx].sataltitude);

        // Display Satellite Azimuth
        satWindow->ui->azmLCD->display(positions[currentIdx].azimuth);

        // Delay of 2 seconds
        delay(2000);

        // Go to next Position
        currentIdx++;
    }


}


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

    // Start the timer to update the progress every 30 milliseconds
    timer.start(20);

    // Show the progress dialog
    progressDialog.exec();
}


void AstroNaviArm::on_huble_btn_clicked()
{


    double az = 120;
    double alt = 150;
    sendCommand(az, alt);

}


void AstroNaviArm::on_noaa_btn_clicked()
{
    for (int i = 0; i < 36; i++)
    {
        sendCommand(10*i,10*i);
        delay(1000);
    }
}


void AstroNaviArm::on_iridium_btn_clicked()
{
    int maxStep = (int) 360/1.8;
    for(int i = 0; i < maxStep; i++)
    {
        sendCommand(i*1.8, i*1.8);
        delay(1000);
    }
}


void AstroNaviArm::on_goes_btn_clicked()
{
    int step = 0;
    while(1)
    {
        sendCommand(step, step);
        step += 50;
    }
}

