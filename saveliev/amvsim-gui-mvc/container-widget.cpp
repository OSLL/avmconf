#include "container-widget.h"
#include "api/ContainerInfo.h"
#include "api/ContainerState.h"
#include <iostream>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

ContainerWidget::ContainerWidget(QString contName, DeviceModel* model, QObject *parent)
    : m_contName(contName), m_model(model) {
    setLayout(new QHBoxLayout);

    m_powerButton = new QPushButton("Run");
    m_powerButton->setFixedWidth(70);
    QObject::connect(m_powerButton, SIGNAL(pressed()), this, SLOT(powerPressed()));

    m_nameLabel = new QLabel(contName);

    m_switchButton = new QPushButton("Switch here");
    m_switchButton->setVisible(false);
    QObject::connect(m_switchButton, SIGNAL(pressed()), this, SLOT(switchHerePressed()));

    layout()->addWidget(m_powerButton);
    layout()->addWidget(m_nameLabel);
    ((QHBoxLayout*)layout())->addWidget(m_switchButton, 0, Qt::AlignRight);

    setAutoFillBackground(true);
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

void ContainerWidget::powerPressed() {
    if (m_model->device()->getContainerInfo(m_contName.toStdString()).state == StateStopped) {
        m_model->device()->startContainer(m_contName.toStdString());
        m_powerButton->setText("Stop");
        m_switchButton->setVisible(true);

//        if (m_model->device()->getActiveContainer() == m_contName.toStdString()) {
//            highlightAsActive();
//        }
    } else {
        m_model->device()->stopContainer(m_contName.toStdString());
        m_powerButton->setText("Run");
        m_switchButton->setVisible(false);
    }
}

void ContainerWidget::switchHerePressed() {
    if (m_model->device()->getContainerInfo(m_contName.toStdString()).state == StateRunning) {
        m_model->device()->switchToContainer(m_contName.toStdString());
        highlightAsActive();
    }
}

void ContainerWidget::highlightAsActive() {
    setPalette(QPalette( Qt::blue ) );
}




