
#include <QtGui/QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    system("open device");

    return a.exec();
}
