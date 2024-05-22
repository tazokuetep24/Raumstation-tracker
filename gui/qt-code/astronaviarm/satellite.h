#ifndef SATELLITE_H
#define SATELLITE_H

#include <QDialog>

namespace Ui {
class Satellite;
}

class Satellite : public QDialog
{
    Q_OBJECT

public:
    int satID;
    explicit Satellite(QWidget *parent = nullptr);
    ~Satellite();
    Ui::Satellite *ui;
private slots:
    //void on_pushButton_clicked();
    void on_trackBtn_clicked();
};

#endif // SATELLITE_H
