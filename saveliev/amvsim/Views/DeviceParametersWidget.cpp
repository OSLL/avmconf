#include "DeviceParametersWidget.h"

DeviceParametersWidget::DeviceParametersWidget(IDevice *device, QWidget *parent)
    : QWidget(parent), m_device(device)
{
}
