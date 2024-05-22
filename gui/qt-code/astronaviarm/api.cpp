#include "api.h"
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


/**
 * @brief Retrieves the position of a satellite.
 *
 * This function makes an API request to obtain the position of a satellite at a given time.
 *
 * @note The Used API is N2YO
 *
 * @param noradId The NORAD ID of the satellite.
 * @param observerLat The latitude of the observer's location.
 * @param observerLng The longitude of the observer's location.
 * @param observerAlt The altitude of the observer's location.
 * @param seconds The time duration for which to retrieve the satellite's position.
 * @param apiKey The API key for authentication.
 * @param positions An array to store the satellite positions.
 * @return True if the request is successful, false otherwise.
 */
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

