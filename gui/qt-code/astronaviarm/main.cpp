#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AstroNaviArm w;
    w.show();

    return a.exec();
}
