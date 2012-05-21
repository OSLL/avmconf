#include "ParameterWidgets.h"
#include <sstream>

ParameterWidget::ParameterWidget(IDevice *device, const std::string &m_parId, QWidget *parent) 
    : m_device(device), QWidget(parent), m_parId(m_parId)
{
}


BoolParameterWidget::BoolParameterWidget(IDevice *device, const std::string &parId, QWidget *parent)
    : ParameterWidget(device, parId, parent)    
{
}

DoubleParameterWithRangeWidget::DoubleParameterWithRangeWidget(IDevice *device, const std::string &parId, QWidget *parent)
    : ParameterWidget(device, parId, parent)    
{
}

void DoubleParameterWithRangeWidget::editChanged(const QString &val)
{
    m_slider.setValue(val.toInt());
    emit(parameterChanged(m_parId, new DoubleValue(m_parId, val.toDouble())));
}

void DoubleParameterWithRangeWidget::sliderMoved(int newVal)
{
    std::ostringstream strs;
    strs << newVal;    
    m_edit.setText(QString::fromStdString(strs.str()));
    
    emit(parameterChanged(m_parId, new DoubleValue(m_parId, newVal)));
}




OptionsParameterWidget::OptionsParameterWidget(IDevice *device, const std::string &parId, QWidget *parent)
    : ParameterWidget(device, parId, parent)    
{
}

void BoolParameterWidget::checkBoxChanged(int newState)
{
    emit(parameterChanged(m_parId, new BoolValue(m_parId, newState == Qt::Checked)));
}

void OptionsParameterWidget::radioSwitched(int newVal)
{
    emit(parameterChanged(m_parId, new OptionsValue(m_parId, newVal)));
}
