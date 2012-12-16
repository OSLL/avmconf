
#include <QtGui/QApplication>

#include "MainWindow.h"
//#include <api/AndroidDevice.h>

#include <api/Smartphone.h>

int main(int argc, char *argv[])
{
  //IDevice* device = new AndroidDevice;
    IDevice* device = new Smartphone;

    QApplication a(argc, argv);
    MainWindow w(device);
    //w.setWindowState(Qt::WindowFullScreen);
    w.show();

    return a.exec();
}
