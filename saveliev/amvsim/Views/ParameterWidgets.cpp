#include "ParameterWidgets.h"

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

OptionsParameterWidget::OptionsParameterWidget(IDevice *device, const std::string &parId, QWidget *parent)
    : ParameterWidget(device, parId, parent)    
{
}

void BoolParameterWidget::checkBoxChanged(int newState)
{
    emit(parameterChanged(m_parId, new BoolValue(m_parId, newState == Qt::Checked)));
}


void DoubleParameterWithRangeWidget::sliderMoved(double newVal)
{
    emit(parameterChanged(m_parId, new DoubleValue(m_parId, newVal)));
}


void OptionsParameterWidget::radioSwitched(int newVal)
{
    emit(parameterChanged(m_parId, new OptionsValue(m_parId, newVal)));
}
