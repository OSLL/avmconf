
#include <QtGui/QApplication>

#include "MainWindow.h"
#include <api/AndroidDevice.h>

int main(int argc, char *argv[])
{
    IDevice* device = new AndroidDevice;

    QApplication a(argc, argv);
    MainWindow w(device);
    w.show();

    return a.exec();
}
