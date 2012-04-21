
#include <QtGui/QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    AndroidDevice* device = new AndroidDevice;

    QApplication a(argc, argv);
    MainWindow w(device);
    w.show();

    system("open device");

    return a.exec();
}
