#ifndef CONTAINERPARAMETERSWIDGET_H
#define CONTAINERPARAMETERSWIDGET_H

#include <QWidget>
#include <QLabel>

#include "api/IDevice.h"
#include "ParameterWidgets.h"

class ParametersWidget : public QWidget
{
    Q_OBJECT
    
private:
    IDevice *m_device;    
    
    void initWidgetsForParameters(const std::vector<Parameter*> &parameters);
    QLabel *buildServiceLabel(QLabel *label);
    
    ParameterWidget *buildBoolean        (BoolParameter *par, bool val);
    ParameterWidget *buildDoubleWithRange(DoubleParameterWithRange *par, double val);
    ParameterWidget *buildOptions        (OptionsParameter *par, int val);
    
public:
    ParametersWidget(IDevice *device, const std::vector<Parameter*>& parameters, QWidget *parent = 0);
    
signals:
     
};

#endif // CONTAINERPARAMETERSWIDGET_H
