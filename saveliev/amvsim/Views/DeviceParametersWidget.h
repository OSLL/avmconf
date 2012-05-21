#ifndef DEVICEPARAMETERSWIDGET_H
#define DEVICEPARAMETERSWIDGET_H

#include <QWidget>
#include <api/IDevice.h>

class DeviceParametersWidget : public QWidget
{
    Q_OBJECT
private:
    IDevice *m_device;
    
public:
    explicit DeviceParametersWidget(IDevice *device, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // DEVICEPARAMETERSWIDGET_H
