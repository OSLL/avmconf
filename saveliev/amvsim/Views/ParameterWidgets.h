#ifndef PARAMETERWIDGETS_H
#define PARAMETERWIDGETS_H

#include <QWidget>
#include <api/Parameter.h>
#include <api/IDevice.h>
#include <QLineEdit>
#include <QSlider>

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

class BoolParameterWidget : public ParameterWidget 
{
    Q_OBJECT
    
public:
    BoolParameterWidget(IDevice *device, const std::string& parId, QWidget *parent = 0);
    
public slots:
    void checkBoxChanged(int);    
};

class DoubleParameterWithRangeWidget : public ParameterWidget 
{
    Q_OBJECT
private:
    QSlider m_slider;
    QLineEdit m_edit;
    
public:
    DoubleParameterWithRangeWidget(IDevice *device, const std::string& parId, QWidget *parent = 0);
    
public slots:
    void editChanged(const QString&);
    void sliderMoved(int);    
};

class OptionsParameterWidget : public ParameterWidget 
{
    Q_OBJECT
    
public:
    OptionsParameterWidget(IDevice *device, const std::string& parId, QWidget *parent = 0);
    
public slots:
    void radioSwitched(int);    
};

#endif // PARAMETERWIDGETS_H
