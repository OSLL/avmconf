#ifndef LISTPARAMETERWIDGET_H
#define LISTPARAMETERWIDGET_H

#include "ParameterWidget.h"

class ListParameterWidget : public ParameterWidget
{
    Q_OBJECT
public:
    explicit ListParameterWidget(IDevice *device, OptionsParameter *par, int val, QWidget *parent = 0);
    
signals:
    
public slots:
    void switched(int);    
};

#endif // LISTPARAMETERWIDGET_H
