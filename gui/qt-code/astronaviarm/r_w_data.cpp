#include "r_w_data.h"
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QThread>
#include <QTimer>



//
bool getSatellitePosition(int noradId, double observerLat, double observerLng,
                          double observerAlt, int seconds, const QString& apiKey,
                          satPos positions[MAX_REQUEST])
{
    // URL of the API
    QString url = QString("https://api.n2yo.com/rest/v1/satellite/positions/%1/%2/%3/%4/%5&apiKey=%6")
                      .arg(noradId)
                      .arg(observerLat)
                      .arg(observerLng)
                      .arg(observerAlt)
                      .arg(seconds)
                      .arg(apiKey);

    // Create a network manager
    QNetworkAccessManager manager;

    // Make the API request
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

    // Wait for the reply to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {

        // Read the data from the reply
        QByteArray responseData = reply->readAll();

        // Parse JSON response
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject response = jsonResponse.object();

        // Save Positions
        for (int i = 0; i < MAX_REQUEST; i++)
        {
            positions[i].azimuth = response["positions"][i]["azimuth"].toDouble();
            positions[i].elevation = response["positions"][i]["elevation"].toDouble();
            positions[i].sataltitude = response["positions"][i]["sataltitude"].toDouble();
            positions[i].satlatitude = response["positions"][i]["satlatitude"].toDouble();
            positions[i].satlongitude = response["positions"][i]["satlongitude"].toDouble();
        }
        return 1;

    } else {
        // Handle the error
        qDebug() << "Error:" << reply->errorString();
        return 0; // Return an empty object in case of an error
    }
}

//
QString formatDouble(double d) {
    return QString("%1").arg(d, 7, 'f', 3, '0');
}

//
void sendCommand(double satAz, double satAlt, const QString& comPort, qint32 baudRate) {
    try {
        // Open the serial port
        QSerialPort serial;
        serial.setPortName(comPort);
        serial.setBaudRate(baudRate);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        if (serial.open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port" << comPort << "opened successfully.";

            // Send the command
            QString command = formatDouble(satAz) + " " + formatDouble(satAlt) + "\n";
            serial.write(command.toUtf8());
            qDebug() << "Command '" << command << "' sent to" << comPort << ".";

            // Wait for a moment to allow the STM32 to process the command
            delay(1000);

            // Close the serial port
            serial.close();
            qDebug() << "Serial port closed.";
        } else {
            qDebug() << "Error opening serial port" << comPort << ": " << serial.errorString();
        }

    } catch (const std::exception& e) {
        qDebug() << "Error:" << e.what();
    }
}

//
void delay(double timeInMs)
{

    // Introduce delay
    QEventLoop loop;
    QTimer::singleShot(timeInMs, &loop, &QEventLoop::quit);
    loop.exec();

}
