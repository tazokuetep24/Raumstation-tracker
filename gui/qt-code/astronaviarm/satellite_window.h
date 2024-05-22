#ifndef SATELLITE_WINDOW_H
#define SATELLITE_WINDOW_H

#include <QDialog>
#include <QSerialPort>
#include <QPushButton>
#include "api.h"

namespace Ui {
class Satellite;
}

class Satellite : public QDialog
{
    Q_OBJECT

public:

    /**
    * @brief Constructor of the class Satellite
    */
    explicit Satellite(QWidget *parent = nullptr);
    /**
    * @brief Destructor of the class Satellite
    */
    ~Satellite();
    Ui::Satellite *ui;
    /**
    * @brief Handles the close event for the satellite control window.
    */
    void closeEvent(QCloseEvent *event) override;
    /**
    * @brief Initiates satellite tracking and updates the UI with real-time position data.
    */
    void updateLCD(int currentPosition);
    /**
    * @brief Initiates satellite tracking and updates the UI with real-time position data.
    */
    void start();

    int satID;   ///<  Id of the satellite to track
private slots:
    /**
    * @brief Handles the button click event for tracking the satellite position.
    */
    void on_trackBtn_clicked();
    /**
    * @brief Handles the "Stop" button click event.
    */
    void handleSerialData();
    /**
    * @brief Handles the "Go Back to initial position" button click event.
    */
    void onStopClicked();
    /**
    * @brief Updates the LCD displays with satellite position information.
    */
    void onGoBackClicked();
    /**
     * @brief showErrorDialog
     */
    void showErrorDialog(QString title, QString message);
private:
    QSerialPort * serialPort;      ///<  Pointer to the serial port used for communication with external devices
    bool limitIsReached;           ///<  Flag indicating whether a positional limit has been reached
    QPushButton *stop;             ///<  Button for stopping the satellite tracking movement
    QPushButton *goback;           ///<  Button for moving the satellite tracking back
    satPos positions[MAX_REQUEST]; ///<  Array to store satellite positions with a maximum request limit
    bool trackIsPressed;           ///<  Flag indicating whether the satellite tracking is in a pressed state

};

#endif // SATELLITE_WINDOW_H
