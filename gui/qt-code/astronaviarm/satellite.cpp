#include "satellite.h"
#include "ui_satellite.h"
#include "r_w_data.h"
#include <QDebug>

Satellite::Satellite(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Satellite)
{
    ui->setupUi(this);
}

Satellite::~Satellite()
{
    delete ui;
}



void Satellite::on_trackBtn_clicked()
{

    satPos positions[MAX_REQUEST];
    bool gotSatPos = getSatellitePosition(satID, MY_LATITUDE, MY_LONGITUDE,
                                          MY_ALTITUDE, MAX_REQUEST, API_KEY, positions);
    int currentIdx = 0;
    if (gotSatPos)
    {
        while(1)
        {
            // Reached last position
            if (currentIdx == MAX_REQUEST - 1)
            {
                // Load Data again
                bool _unused = getSatellitePosition(satID, MY_LATITUDE, MY_LONGITUDE,
                                                    MY_ALTITUDE, MAX_REQUEST, API_KEY, positions);
                currentIdx = 0;
            }

            // Send Current Position
            sendCommand(positions[currentIdx].azimuth, positions[currentIdx].elevation, "COM4");
            currentIdx++;
            delay(1500);
        }
    }
    else
    {
        qDebug() << "Error loading satellite data";
    }
}

