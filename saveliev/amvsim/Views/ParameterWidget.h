#ifndef PARAMETERWIDGETS_H
#define PARAMETERWIDGETS_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>

#include "api/Parameter.h"
#include "api/IDevice.h"

class ParameterWidget : public QWidget
{
    Q_OBJECT

protected:
    IDevice *m_device;
    std::string m_parId;
    
public:
    ParameterWidget(IDevice *device, const std::string& parId, QWidget *parent = 0);
    
signals:
    void parameterChanged(const std::string& parId, Value *value);
    
public slots:
    
};
#endif // PARAMETERWIDGETS_H
