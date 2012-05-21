#ifndef DOUBLEPARAMETERWITHRANGEWIDGET_H
#define DOUBLEPARAMETERWITHRANGEWIDGET_H

#include "ParameterWidget.h"

class DoubleParameterWithRangeWidget : public ParameterWidget 
{
    Q_OBJECT
    
private:
    QSlider *m_slider;
    QLineEdit *m_edit;
    
public:
    DoubleParameterWithRangeWidget(IDevice *device, DoubleParameterWithRange *par, double val, QWidget *parent = 0);
    
public slots:
    void editChanged(const QString&);
    void sliderMoved(int);    
};

#endif // DOUBLEPARAMETERWITHRANGEWIDGET_H
