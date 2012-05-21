
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

#include "DeviceParametersDialog.h"

DeviceParametersDialog::DeviceParametersDialog(IDevice *device, QWidget *parent) :
    QDialog(parent), m_device(device)
{
    setWindowTitle("Device parameters");
    setLayout(new QVBoxLayout);
    setFixedWidth(400);
            
    QWidget *parameters = initParameters();
    QWidget *buttons = initButtons();
    
    parameters->setFixedHeight(400);
    
    ((QVBoxLayout*)layout())->setContentsMargins(0, 0, 0, 0);
    ((QVBoxLayout*)layout())->addWidget(parameters, 0, Qt::AlignTop);      
    ((QVBoxLayout*)layout())->addWidget(buttons, 0, Qt::AlignBottom);     
    
    setTabOrder(buttons, parameters);   
}

QWidget *DeviceParametersDialog::initParameters()
{
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(new ParametersWidget(m_device, m_device->getDeviceParametersList()));    
    return scrollArea;
}

QWidget *DeviceParametersDialog::initButtons()
{        
    m_doneButton = new QPushButton("Done");  
    
    QWidget *w = new QWidget;
    w->setLayout(new QHBoxLayout);
    ((QHBoxLayout*)w->layout())->setContentsMargins(15, 0, 15, 15);
    ((QHBoxLayout*)w->layout())->addWidget(m_doneButton, 0, Qt::AlignLeft);
    
    connect(m_doneButton, SIGNAL(pressed()), this, SLOT(accept()));
    
    return w;
}


