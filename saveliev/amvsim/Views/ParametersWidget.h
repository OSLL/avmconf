#ifndef CONTAINERPARAMETERSWIDGET_H
#define CONTAINERPARAMETERSWIDGET_H

#include <QWidget>
#include <QLabel>

#include "api/IDevice.h"

class ParametersWidget : public QWidget
{
    Q_OBJECT
    
private:
    IDevice *m_device;    
    
    void initWidgetsForParameters(const std::vector<Parameter*> &parameters);
    QLabel *buildServiceLabel(QLabel *label);
    
    static void buildBoolean        (QWidget *w, BoolParameter *par, bool val);
    static void buildDoubleWithRange(QWidget *w, DoubleParameterWithRange *par, double val);
    static void buildOptions        (QWidget *w, OptionsParameter *par, int val);
    
public:
    ParametersWidget(IDevice *device, const std::vector<Parameter*>& parameters, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CONTAINERPARAMETERSWIDGET_H
