
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
    setFixedHeight(100);

    QHBoxLayout* hbl = new QHBoxLayout();
    setLayout(hbl);

    m_powerButton = new QPushButton("Run");
    //m_powerButton->setFixedWidth(70);
    m_powerButton->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_powerButton->setFixedHeight(95);
    QObject::connect(m_powerButton, SIGNAL(pressed()), this, SLOT(powerPressed()));

    m_nameLabel = new QLabel(m_contName);
    m_nameLabel->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_nameLabel->setFixedHeight(95);

    m_switchButton = new QPushButton("Switch\nhere");
    //m_switchButton->setVisible(false);
    m_switchButton->setEnabled(false);
    m_switchButtons->push_back(m_switchButton);
    m_switchButton->setFixedHeight(95);
    QObject::connect(m_switchButton, SIGNAL(pressed()), this, SLOT(switchHerePressed()));

    hbl->addWidget(m_powerButton, 1, Qt::AlignLeft);
    hbl->addWidget(m_nameLabel, 2, Qt::AlignLeft);
    hbl->addWidget(m_switchButton, 1, Qt::AlignRight);
        
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

	m_switchButton->setEnabled(true);

	/*
        m_switchButton->setVisible(true);
        for (int i = 0; i != m_switchButtons->size(); ++i) {
            QPushButton* button = ((QPushButton*)(*m_switchButtons)[i]);
            if (button != m_switchButton)
                button->setEnabled(true);
        }
        m_switchButton->setEnabled(false);
	*/
     // if (m_model->device()->getActiveContainer() == m_contName.toStdString())
     //     highlightAsActive();
    } else {
        m_model->stopContainer(m_contName);
        m_powerButton->setText("Run");
	m_switchButton->setEnabled(false);
        //m_switchButton->setVisible(false);
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
        //m_switchButton->setEnabled(false);
    }
}

void ContainerWidget::highlightAsActive()
{
    //setPalette(QPalette(Qt::blue));
}


