#ifndef OPTIONSPARAMETERWIDGET_H
#define OPTIONSPARAMETERWIDGET_H

#include <QWidget>

#include "ParameterWidget.h"

class OptionsParameterWidget : public ParameterWidget 
{
    Q_OBJECT
    
public:
    OptionsParameterWidget(IDevice *device, OptionsParameter *par, int value, QWidget *parent = 0);
    
public slots:
    void radioSwitched(int);    
};


#endif // OPTIONSPARAMETERWIDGET_H
