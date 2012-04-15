#include <QtCore/QCoreApplication>
#include <QTimer>
#include "AndroidDevice.h"
#include "tests.h"

class Starter : public QCoreApplication
{

public:

    Starter(int argc, char *argv[]):QCoreApplication(argc, argv){
    }

    int exec(){
        AndroidDevice testDevice;
        StorageDescriptor testDescriptor;
        testDevice.createContainer("ubuntu", testDescriptor);
        return 0;
    }

    virtual ~Starter(){
    }

};

int main(int argc, char *argv[])
{
    //Tests::runTests();

    Starter a(argc, argv);

    //QTimer::singleShot(500, &a, SLOT(start()));

    return a.exec();
}
