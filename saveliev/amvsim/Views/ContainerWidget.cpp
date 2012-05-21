
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "../api/ContainerInfo.h"
#include "../api/ContainerState.h"
#include "ContainerWidget.h"

ContainerWidget::ContainerWidget(QVariant contName, QAbstractItemModel *model, 
                                 QWidget *parent, QMap<QString, ContainerWidget*> *anotherContainerWidgets)
    : QWidget(parent), 
      m_contName(contName.toString()), 
      m_model((ContainerListModel*)model),
      m_anotherContainerWidgets(anotherContainerWidgets)      
{
    setLayout(new QHBoxLayout);

    m_powerButton = new QPushButton("Run");
    m_powerButton->setFixedWidth(70);
    QObject::connect(m_powerButton, SIGNAL(pressed()), this, SLOT(powerPressed()));

    m_nameLabel = new QLabel(m_contName);

    m_switchButton = new QPushButton("Switch here");
    m_switchButton->setEnabled(false);
    QObject::connect(m_switchButton, SIGNAL(pressed()), this, SLOT(switchHerePressed()));
    
    ((QHBoxLayout*)layout())->addWidget(m_powerButton);
    ((QHBoxLayout*)layout())->addWidget(m_nameLabel);
    ((QHBoxLayout*)layout())->addWidget(m_switchButton, 0, Qt::AlignRight);
        
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
        m_powerButton->setText("Stop");          
        highlightAsActive();          
        highlightTheRestRunningAsInactive();
        
    } else {        
        m_model->stopContainer(m_contName);
        m_powerButton->setText("Run");
        m_switchButton->setEnabled(false);        
        highlightAsStopped();
    }
}

void ContainerWidget::switchHerePressed()
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
    m_switchButton->setEnabled(false);   
    m_nameLabel->setStyleSheet("font-weight: bold"); 
}

void ContainerWidget::highlightAsStopped()
{
    m_nameLabel->setStyleSheet("font-weight: normal");    
}

void ContainerWidget::highlightRunningAsInactive()
{      
    if (m_model->getContainerInfo(m_contName).state == StateRunning) {
        m_switchButton->setEnabled(true);
        m_nameLabel->setStyleSheet("font-weight: normal");
    }
}



