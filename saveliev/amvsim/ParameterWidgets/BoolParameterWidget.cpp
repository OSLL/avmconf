
#include <QVBoxLayout>

#include "BoolParameterWidget.h"

BoolParameterWidget::BoolParameterWidget(IDevice *device, BoolParameter *par, bool val, QWidget *parent)
    : ParameterWidget(device, par->getId(), parent)    
{
    setLayout(new QVBoxLayout());
    
    m_checkBox = new QCheckBox(par->getName().c_str());
    m_checkBox->setChecked(val);    
    QObject::connect(m_checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkBoxChanged(int)));
    
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->addWidget(m_checkBox);
}

void BoolParameterWidget::checkBoxChanged(int newState)
{
    emit(parameterChanged(m_parId, new BoolValue(m_parId, newState == Qt::Checked)));
}
