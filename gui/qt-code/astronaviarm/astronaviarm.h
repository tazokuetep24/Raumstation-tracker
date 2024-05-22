#ifndef ASTRONAVIARM_H
#define ASTRONAVIARM_H

#include <QMainWindow>
#include "satellite.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AstroNaviArm;
}
QT_END_NAMESPACE

class AstroNaviArm : public QMainWindow
{
    Q_OBJECT

public:
    AstroNaviArm(QWidget *parent = nullptr);
    ~AstroNaviArm();
    void showLoadingBox();

private slots:
    void on_iss_btn_clicked();

    void on_huble_btn_clicked();

    void on_noaa_btn_clicked();

    void on_iridium_btn_clicked();

    void on_goes_btn_clicked();

private:
    Ui::AstroNaviArm *ui;
    Satellite *satWindow;
};
#endif // ASTRONAVIARM_H
