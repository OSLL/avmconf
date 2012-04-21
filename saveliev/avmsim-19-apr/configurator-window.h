#ifndef CONFIGURATORWINDOW_H
#define CONFIGURATORWINDOW_H

#include <QWidget>
#include <QVBoxLayout>

#include "api/AndroidDevice.h"

class ConfiguratorWindow : public QWidget {
    Q_OBJECT

private:
    QWidget *m_containersWidget;
    AndroidDevice *m_device;
    QString m_storageFileName;

    void loadFromFile(AndroidDevice *device);

public:
    explicit ConfiguratorWindow(AndroidDevice *device, QWidget *parent = 0);

signals:

public slots:
    void startAddContainer();
    void addContainerWidget();

};

#endif // CONFIGURATORWINDOW_H
