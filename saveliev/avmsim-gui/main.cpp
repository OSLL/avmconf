//#include <QtGui/QApplication>
//#include "qmlapplicationviewer.h"

#include <QApplication>

#include "configurator-window.h"

#include "api/AndroidDevice.h"

Q_DECL_EXPORT int main(int argc, char *argv[]) {
//    QScopedPointer<QApplication> app(createApplication(argc, argv));
//    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

//    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer->setMainQmlFile(QLatin1String("qml/AndroidVMConfigurator/main.qml"));
//    viewer->showExpanded();

    QApplication app(argc, argv);

    AndroidDevice *device = new AndroidDevice;

    ConfiguratorWindow window(device);

    window.show();

    return app.exec();
}
