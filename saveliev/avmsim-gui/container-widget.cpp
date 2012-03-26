
#include <string>
#include <QHBoxLayout>
#include <QPushButton>

#include "container-widget.h"

ContainerWidget::ContainerWidget(AndroidDevice *device, QString containerName, QWidget *parent)
    : m_device(device),
      QWidget(parent),
      m_nameLabel(new QLabel(containerName, this)),
      m_nameEdit(new QLineEdit(containerName, this)) {

    setLayout(new QHBoxLayout);

    m_nameEdit->setVisible(false);
    ((QHBoxLayout*)layout())->addWidget(m_nameLabel, 1, Qt::AlignLeft);
    ((QHBoxLayout*)layout())->addWidget(m_nameEdit, 1, Qt::AlignLeft);
    QObject::connect(m_nameEdit, SIGNAL(returnPressed()), this, SLOT(setName()));

    m_startButton = new QPushButton("Start");
    m_stopButton = new QPushButton("Stop");
    m_stopButton->setEnabled(false);
    ((QHBoxLayout*)layout())->addWidget(m_startButton, 0, Qt::AlignRight);
    ((QHBoxLayout*)layout())->addWidget(m_stopButton, 0, Qt::AlignRight);
    QObject::connect(m_startButton, SIGNAL(pressed()), this, SLOT(start()));
    QObject::connect(m_stopButton, SIGNAL(pressed()), this, SLOT(stop()));
}

void ContainerWidget::changeName() {
    m_nameEdit->setText(m_nameLabel->text());
    m_nameLabel->setVisible(false);
    m_nameEdit->setVisible(true);
}

void ContainerWidget::setName() {
    m_nameLabel->setText(m_nameEdit->text());
    m_nameLabel->setVisible(true);
    m_nameEdit->setVisible(false);
}

void ContainerWidget::start() {
    m_stopButton->setEnabled(true);
    m_startButton->setEnabled(false);

    m_device->startContainer(m_nameLabel->text().toStdString());
}

void ContainerWidget::stop() {
    m_stopButton->setEnabled(false);
    m_startButton->setEnabled(true);

    m_device->stopContainer(m_nameLabel->text().toStdString());
}

