#include "container-widget.h"
#include "api/container-info.h"
#include <iostream>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

ContainerWidget::ContainerWidget(ContainerInfo info, QObject *parent) {
    setLayout(new QHBoxLayout);

    m_powerButton = new QPushButton("Start");
    m_label = new QLabel(QString::fromStdString(info.name));
    layout()->addWidget(m_powerButton);
    layout()->addWidget(m_label);

    setAutoFillBackground(true);
}

