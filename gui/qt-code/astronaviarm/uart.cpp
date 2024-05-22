#include "uart.h"
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
#include <QMessageBox>


/**
 * @brief Formats a double value as a string.
 *
 * This function converts a double value to a string in this specified format:
 *
 * The double value d will be formatted so it has always the length 6. Also respectivly
 * 3 digits before and after the comma. This is done by adding leading zeros before and
 * after the comma.
 *
 * Examples :  73.12  ---> "073.120"
 *             123.2  ---> "123.200"
 *
 * @param d The double value to be formatted.
 * @return The formatted string representation of the double value.
 */
QString formatDouble(double d) {
    return QString("%1").arg(d, 7, 'f', 3, '0');
}
/**
 * @brief Sends the satellite position over a specified serial port.
 *
 * This function sends the satellite position, consisting of azimuth (satAz) and altitude (satAlt),
 * to the specified serial port. The position is formatted as "xxx.xxx yyy.yyy\n", where satAz and satAlt
 * are first formatted using the formatDouble() function.
 *
 * @param satAz The azimuth value for the satellite.
 * @param satAlt The altitude value for the satellite.
 * @param comPort The name of the serial port (default is "COM3").
 * @param baudRate The baud rate for the serial communication (default is 115200).
 */
bool sendPosition(double satAz, double satAlt, const QString& comPort, qint32 baudRate) {
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
            return true;
        } else {
            qDebug() << "Cannot open serial Port.";
            return false;
        }
    } catch (const std::exception& e) {
        qDebug() << "Error:" << e.what();
        return false;
    }
}
/**
 * @brief Introduces a delay in milliseconds.
 *
 * This function pauses the execution for a specified duration.
 *
 * @param timeInMs The duration of the delay in milliseconds.
 */
void delay(double timeInMs)
{
    // Introduce delay
    QEventLoop loop;
    QTimer::singleShot(timeInMs, &loop, &QEventLoop::quit);
    loop.exec();
}

