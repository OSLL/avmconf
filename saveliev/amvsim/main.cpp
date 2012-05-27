
#include <QtGui/QApplication>

#include "MainWindow.h"

#ifdef DESKTOP
#include <api/AndroidDevice.h>
#endif

#ifdef SMARTPHONE
#include <api/Smartphone.h>
#endif

int main(int argc, char *argv[])
{
    IDevice* device;
    
#if defined(DESKTOP)
    device = new AndroidDevice;
#elif defined(SMARTPHONE)
    device = new Smartphone;
#endif

    QApplication a(argc, argv);
    MainWindow w(device);

#ifdef SMARTPHONE
    w.setWindowState(Qt::WindowFullScreen);
#endif

    w.show();
    
    int res = a.exec();
    delete device;
    return res;
}
