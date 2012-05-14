#ifndef CONTAINERPARAMETERSWIDGET_H
#define CONTAINERPARAMETERSWIDGET_H

#include <QWidget>
#include "api/AndroidDevice.h"

class ContainerParametersWidget : public QWidget
{
    Q_OBJECT
private:
    AndroidDevice *m_device;
    
public:
    explicit ContainerParametersWidget(AndroidDevice* device, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CONTAINERPARAMETERSWIDGET_H
