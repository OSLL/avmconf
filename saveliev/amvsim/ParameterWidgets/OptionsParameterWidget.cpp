
#include <QButtonGroup>
#include <QLabel>
#include <QVBoxLayout>

#include "OptionsParameterWidget.h"

#include <QRadioButton>

OptionsParameterWidget::OptionsParameterWidget(IDevice *device, OptionsParameter *par, int val, QWidget *parent)
    : ParameterWidget(device, par->getId(), parent)    
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);  
    layout()->setSpacing(0);
    
    QLabel *label = new QLabel(par->getName().c_str());  
    layout()->addWidget(label);
    
    QButtonGroup *radios = new QButtonGroup();    
    QObject::connect(radios, SIGNAL(buttonClicked(int)), this, SLOT(radioSwitched(int)));
    QRadioButton *rb;
    for (unsigned i = 0; i != par->getOptions().size(); ++i) {
        rb = new QRadioButton(par->getOptions()[i].data());
        rb->setStyleSheet("margin-bottom: 5px");  
        radios->addButton(rb);
        layout()->addWidget(rb);
        if (i == val) {
            rb->setChecked(true);
        }
    }
    rb->setStyleSheet("margin-bottom: 7px");  
}

void OptionsParameterWidget::radioSwitched(int newVal)
{
    emit(parameterChanged(m_parId, new OptionsValue(m_parId, newVal)));
}
