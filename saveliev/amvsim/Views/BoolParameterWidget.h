#ifndef BOOLPARAMETERWIDGET_H
#define BOOLPARAMETERWIDGET_H

#include <QCheckBox>

#include "ParameterWidget.h"

class BoolParameterWidget : public ParameterWidget 
{
    Q_OBJECT
    
private:
    QCheckBox *m_checkBox;
    
public:
    BoolParameterWidget(IDevice *device, BoolParameter *par, bool val, QWidget *parent = 0);
    
public slots:
    void checkBoxChanged(int);    
};

#endif // BOOLPARAMETERWIDGET_H
