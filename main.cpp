#include <QtCore/QCoreApplication>
#include <QTimer>
#include "AndroidDevice.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    Tests::runTests();

    QCoreApplication a(argc, argv);

    QTimer::singleShot(500, &a, SLOT(quit()));

    return a.exec();
}
