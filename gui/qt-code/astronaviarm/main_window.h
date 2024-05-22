#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "satellite_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AstroNaviArm;
}
QT_END_NAMESPACE

class AstroNaviArm : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor of the class AstroNaviArm
     */
    AstroNaviArm(QWidget *parent = nullptr);
    /**
     * @brief Default destructor of the class AstroNaviArm
     */
    ~AstroNaviArm();
    /**
     * @brief Displays a loading dialog to simulate the process of loading satellite position data.
     */
    void showLoadingBox();
private slots:
     /**
     * @brief Handles the button click event to track the ISS Satellite.
     */
    void on_iss_btn_clicked();
    /**
     * @brief Handles the button click event to track the Hubble Satellite.
     */
    void on_huble_btn_clicked();
    /**
     * @brief Handles the button click event to track the NOAA Satellite.
     */
    void on_noaa_btn_clicked();
    /**
     * @brief Handles the button click event to track the Iridium Satellite.
     */
    void on_iridium_btn_clicked();
    /**
     * @brief Handles the button click event to track the GOES Satellite.
     */
    void on_goes_btn_clicked();
    /**
     * @brief Handles the button click event to track the Tiangong Satellite.
     */
    void onTiangongButtonClicked();
    /**
     * @brief Handles the button click event to track the Starlink Satellite.
     */
    void onStarlinkButtonClicked();
private:
    Ui::AstroNaviArm *ui;
    Satellite *satWindow; ///< Satellite winodow
};
#endif // MAIN_WINDOW_H
