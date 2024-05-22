#ifndef API_H
#define API_H

#include <QString>
#include <QJsonObject>

// Constants defining the observer's location, API key, and maximum number of requests
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


/**
 * @brief Retrieves the position of a satellite.
 *
 * This function makes an API request to obtain the position of a satellite at a given time.
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
                          satPos positions[MAX_REQUEST]);


#endif // API_H
