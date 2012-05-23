
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>

#include "api/ContainerInfo.h"
#include "api/ContainerState.h"
#include "ContainerWidget.h"
#include "PowerButton.h"
#include "SwitchButton.h"

ContainerWidget::ContainerWidget(QVariant contName, QAbstractItemModel *model, 
                                 QWidget *parent, QMap<QString, ContainerWidget*> *anotherContainerWidgets)
    : QWidget(parent), 
      m_contName(contName.toString()), 
      m_model((ContainerListModel*)model),
      m_anotherContainerWidgets(anotherContainerWidgets)      
{
    QHBoxLayout *lay = new QHBoxLayout();
    setLayout(lay);

    m_powerButton = new TextPowerButton();
    m_powerButton->setOff();
    QObject::connect(m_powerButton, SIGNAL(pressed()), this, SLOT(powerPressed()));

    m_nameLabel = new QLabel(m_contName);

    m_switchButton = new SwitchButton();
    m_switchButton->setStoppedContainerView();
    QObject::connect(m_switchButton, SIGNAL(pressed()), this, SLOT(switchPressed()));
    
    lay->addWidget(m_powerButton);
    lay->addWidget(m_nameLabel);
    lay->addWidget(m_switchButton, 0, Qt::AlignRight);
        
    setAutoFillBackground(true);
    
    (*m_anotherContainerWidgets).insert(contName.toString(), this);
}

void ContainerWidget::mousePressEvent(QMouseEvent*) 
{
    emit pressed(m_contName);    
}

void ContainerWidget::powerPressed()
{
    if (m_model->getContainerInfo(m_contName).state != StateRunning) {
        m_model->startContainer(m_contName);
        m_powerButton->setOn();
        highlightAsActive();       
        highlightTheRestRunningAsInactive();        
    } else {        
        m_model->stopContainer(m_contName);        
        highlightAsStopped();
    }
}

void ContainerWidget::switchPressed()
{
    if (m_model->getContainerInfo(m_contName).state == StateRunning) {
        m_model->switchToContainer(m_contName);  
        highlightAsActive();
        highlightTheRestRunningAsInactive();
    }
}

void ContainerWidget::highlightTheRestRunningAsInactive()
{    
    for (QMap<QString, ContainerWidget*>::Iterator it = m_anotherContainerWidgets->begin(); 
         it != m_anotherContainerWidgets->end(); ++it) {
        ContainerWidget* w = (ContainerWidget*)it.value();
        if (w->m_switchButton != m_switchButton &&
                m_model->getContainerInfo(w->m_contName).state == StateRunning) {  
            
            w->highlightRunningAsInactive();            
        }
    }        
}

void ContainerWidget::highlightAsActive()
{ 
    m_switchButton->setActiveContainerView();
    m_nameLabel->setStyleSheet("font-weight: bold");
}

void ContainerWidget::highlightAsStopped()
{
    m_powerButton->setOff();
    m_switchButton->setStoppedContainerView();
    m_nameLabel->setStyleSheet("font-weight: normal");
}

void ContainerWidget::highlightRunningAsInactive()
{      
    if (m_model->getContainerInfo(m_contName).state == StateRunning) {
        m_switchButton->setRunningInactiveContainerView();
        m_nameLabel->setStyleSheet("font-weight: normal");
    }
}



