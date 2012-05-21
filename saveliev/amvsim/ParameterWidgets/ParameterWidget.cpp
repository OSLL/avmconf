#include "ParameterWidget.h"
#include <sstream>

ParameterWidget::ParameterWidget(IDevice *device, const std::string &m_parId, QWidget *parent) 
    : m_device(device), QWidget(parent), m_parId(m_parId)
{
}


