
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

#include "ListParameterWidget.h"

ListParameterWidget::ListParameterWidget(IDevice *device, OptionsParameter *par, int val, QWidget *parent) :
    ParameterWidget(device, par->getId(), parent)
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);  
    layout()->setSpacing(0);
    
    QLabel *label = new QLabel(par->getName().c_str());  
    layout()->addWidget(label);
    
    QListWidget *lw = new QListWidget();
    QObject::connect(lw, SIGNAL(itemSelectionChanged()), this, SLOT(switched(int)));
    
    new QListWidgetItem(tr("Oak"), lw);    
}

void ListParameterWidget::switched(int newVal)
{
    emit(parameterChanged(m_parId, new OptionsValue(m_parId, newVal)));
}
