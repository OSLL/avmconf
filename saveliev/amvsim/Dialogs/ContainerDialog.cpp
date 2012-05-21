#include "ContainerDialog.h"
#include <QVBoxLayout>
#include <QLabel>

ContainerDialog::ContainerDialog(ContainerListModel *model, const QString &contName, QWidget *parent)
    : QDialog(parent), m_model(model), m_contName(contName), m_toDestroy(false)
{
    setWindowTitle(contName);
    setLayout(new QVBoxLayout);
    setFixedWidth(400);
    setMaximumHeight(400);
    layout()->setContentsMargins(7, 7, 7, 7);
        
    QWidget *parameters = initParameters();
    QWidget *buttons = initButtons();
      
    ((QVBoxLayout*)layout())->addWidget(parameters, 0, Qt::AlignTop);      
    ((QVBoxLayout*)layout())->addWidget(buttons, 0, Qt::AlignBottom);     
    
    setTabOrder(buttons, parameters);      
}

QWidget *ContainerDialog::initParameters()
{
    m_parameters = new ParametersWidget(m_model->getDevice(), m_model->getDevice()->getContainerParametersList());    
    return m_parameters;
}

QWidget *ContainerDialog::initButtons()
{        
    m_doneButton = new QPushButton("Done");  
    
    m_destroyButton = new QPushButton("Destroy the container");
    m_destroyButton->setFixedWidth(200);
    m_destroyButton->setStyleSheet("color: red");
    
    m_cancelDestroyButton = new QPushButton("Cancel");
    m_cancelDestroyButton->setVisible(false);
    
    QWidget *w = new QWidget;
    w->setLayout(new QHBoxLayout);    
    ((QHBoxLayout*)w->layout())->setContentsMargins(0, 0, 0, 0);
    ((QHBoxLayout*)w->layout())->addWidget(m_destroyButton);
    ((QHBoxLayout*)w->layout())->addWidget(m_cancelDestroyButton);
    ((QHBoxLayout*)w->layout())->addWidget(m_doneButton, 0, Qt::AlignRight); 
    w->setTabOrder(m_doneButton, m_cancelDestroyButton);      
    w->setTabOrder(m_doneButton, m_destroyButton);       
    w->setTabOrder(m_cancelDestroyButton, m_destroyButton);    
    
    connect(m_destroyButton, SIGNAL(pressed()), this, SLOT(destroyPressed()));
    connect(m_cancelDestroyButton, SIGNAL(pressed()), this, SLOT(cancelDestroyPressed()));
    connect(m_doneButton, SIGNAL(pressed()), this, SLOT(accept()));
    
    return w;
}

void ContainerDialog::destroyPressed()
{
    if (m_toDestroy) {
        m_model->destroyContainer(m_contName);
        accept();
    } else {
        m_destroyButton->setText("Destroy");
        m_destroyButton->setFixedWidth(100);
        m_cancelDestroyButton->setVisible(true);
        m_toDestroy = true;
    }
}

void ContainerDialog::cancelDestroyPressed()
{
    m_toDestroy = false;
    m_destroyButton->setText("Destroy the container");
    m_destroyButton->setFixedWidth(200);
    m_cancelDestroyButton->setVisible(false);
}
