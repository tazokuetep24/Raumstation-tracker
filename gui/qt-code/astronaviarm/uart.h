#ifndef UART_H
#define UART_H

#include <QString>

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
 *
 * @return True if the position is sent successfully, otherwise False
 */
bool sendPosition(double satAz, double satAlt, const QString& comPort = "COM3", qint32 baudRate = 115200);
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
QString formatDouble(double d);

/**
 * @brief Introduces a delay in milliseconds.
 *
 * This function pauses the execution for a specified duration.
 *
 * @param timeInMs The duration of the delay in milliseconds.
 */
void delay(double timeInMs);

#endif // UART_H
