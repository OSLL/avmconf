#include <string>
#include <QHBoxLayout>
#include <QPushButton>

#include "container-view.h"

ContainerView::ContainerView(AndroidDevice *device, const std::string &containerName, QWidget *parent)
    : device(device), QWidget(parent) {

    QHBoxLayout *lay = new QHBoxLayout;
    setLayout(lay);

    nameEdit = new QLineEdit(this);
    nameEdit->setFixedWidth(100);
    nameLabel = new QLabel(this);
    nameLabel->setVisible(false);

    lay->addWidget(nameLabel, 0, Qt::AlignLeft);
    lay->addWidget(nameEdit, 0, Qt::AlignLeft);
    QObject::connect(nameEdit, SIGNAL(returnPressed()), this, SLOT(setName()));

    startButton = new QPushButton("Start");
    stopButton = new QPushButton("Stop");
    stopButton->setEnabled(false);
    lay->addWidget(startButton, 0, Qt::AlignRight);
    lay->addWidget(stopButton, 0, Qt::AlignRight);
    QObject::connect(startButton, SIGNAL(pressed()), this, SLOT(start()));
    QObject::connect(stopButton, SIGNAL(pressed()), this, SLOT(stop()));
}

void ContainerView::setName() {
    nameLabel->setText(nameEdit->text());
    nameLabel->setVisible(true);
    nameEdit->setVisible(false);

 // container = device->createContainer(nameLabel->text().toStdString());
}

void ContainerView::start() {
    stopButton->setEnabled(true);
    startButton->setEnabled(false);

    device->startContainer(nameLabel->text().toStdString());
}

void ContainerView::stop() {
    stopButton->setEnabled(false);
    startButton->setEnabled(true);

    device->stopContainer(nameLabel->text().toStdString());
}

