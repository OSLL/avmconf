
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "../api/ContainerInfo.h"
#include "../api/ContainerState.h"
#include "ContainerWidget.h"

ContainerWidget::ContainerWidget(QVariant contName, QAbstractItemModel *model, 
                                 QWidget *parent, QVector<QPushButton*> *switchButtons)
    : QWidget(parent), 
      m_contName(contName.toString()), 
      m_model((ContainerListModel*)model),
      m_switchButtons(switchButtons)      
{
    setLayout(new QHBoxLayout);

    m_powerButton = new QPushButton("Run");
    m_powerButton->setFixedWidth(70);
    QObject::connect(m_powerButton, SIGNAL(pressed()), this, SLOT(powerPressed()));

    m_nameLabel = new QLabel(m_contName);

    m_switchButton = new QPushButton("Switch here");
    m_switchButton->setVisible(false);
    m_switchButtons->push_back(m_switchButton);
    QObject::connect(m_switchButton, SIGNAL(pressed()), this, SLOT(switchHerePressed()));

    m_destroyButton = new QPushButton("Destroy");
    QObject::connect(m_destroyButton, SIGNAL(pressed()), this, SLOT(destroyContainer()));

    layout()->addWidget(m_powerButton);
    layout()->addWidget(m_nameLabel);
    ((QHBoxLayout*)layout())->addWidget(m_switchButton, 0, Qt::AlignRight);
    ((QHBoxLayout*)layout())->addWidget(m_destroyButton, 0, Qt::AlignRight);

        
    setAutoFillBackground(true);
}

void ContainerWidget::mousePressEvent(QMouseEvent*) 
{
    emit pressed(m_contName);    
}

//void ContainerWidget::start() {
//    m_stopButton->setEnabled(true);
//    m_startButton->setEnabled(false);

//    m_device->startContainer(m_nameLabel->text().toStdString());
//}

//void ContainerWidget::stop() {
//    m_stopButton->setEnabled(false);
//    m_startButton->setEnabled(true);

//    m_device->stopContainer(m_nameLabel->text().toStdString());
//}

void ContainerWidget::powerPressed()
{
    if (m_model->getContainerInfo(m_contName).state == StateStopped) {
        m_model->startContainer(m_contName);
        m_powerButton->setText("Stop");
        m_switchButton->setVisible(true);
        for (int i = 0; i != m_switchButtons->size(); ++i) {
            QPushButton* button = ((QPushButton*)(*m_switchButtons)[i]);
            if (button != m_switchButton)
                button->setEnabled(true);
        }
        m_switchButton->setEnabled(false);
     // if (m_model->device()->getActiveContainer() == m_contName.toStdString())
     //     highlightAsActive();
    } else {
        m_model->stopContainer(m_contName);
        m_powerButton->setText("Run");
        m_switchButton->setVisible(false);
    }
}

void ContainerWidget::switchHerePressed()
{
    if (m_model->getContainerInfo(m_contName).state == StateRunning) {
        m_model->switchToContainer(m_contName);
        highlightAsActive();
        for (int i = 0; i != m_switchButtons->size(); ++i) {
            QPushButton* button = ((QPushButton*)(*m_switchButtons)[i]);
            if (button != m_switchButton)
                button->setEnabled(true);
        }
        m_switchButton->setEnabled(false);
    }
}

void ContainerWidget::highlightAsActive()
{
    setPalette(QPalette(Qt::blue));
}

void ContainerWidget::destroyContainer()
{
    m_model->destroyContainer(m_contName);
}




