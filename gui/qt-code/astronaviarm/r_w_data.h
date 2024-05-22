#ifndef R_W_DATA_H
#define R_W_DATA_H

#include <QString>
#include <QJsonObject>

//
#define MY_LATITUDE 50.776546
#define MY_LONGITUDE 6.083599
#define MY_ALTITUDE 202
#define API_KEY "JWMUC7-MM69YM-GQKJC4-55WB"
#define MAX_REQUEST 300



// Struct holding the position of the satellite
typedef struct Data
{
    double satlatitude =  0;
    double satlongitude = 0;
    double sataltitude =  0;
    double azimuth = 0;
    double elevation = 0;

} satPos;


//
bool getSatellitePosition(int noradId, double observerLat, double observerLng,
                          double observerAlt, int seconds, const QString& apiKey,
                          satPos positions[MAX_REQUEST]);


//
QString formatDouble(double d);

void delay(double timeInMs);

//
void sendCommand(double satAz, double satAlt, const QString& comPort = "COM4", qint32 baudRate = 115200);

#endif // R_W_DATA_H
