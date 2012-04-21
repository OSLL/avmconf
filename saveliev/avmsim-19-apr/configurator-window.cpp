#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include "configurator-window.h"
#include "container-widget.h"
#include "new-container-dialog.h"

ConfiguratorWindow::ConfiguratorWindow(AndroidDevice *device, QWidget *parent)
    : m_device(device), QWidget(parent), m_containersWidget(new QWidget(this)),
      m_storageFileName("storage"){

    this->setWindowTitle("Configurator");
 // TODO: desable height resize // resizeMode to fixed?
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    this->setFixedWidth(500);

    QPushButton *m_addContainerButton = new QPushButton("Create container", this);
    m_addContainerButton->setFixedWidth(140);
 // m_addContainerButton->adjustSize();
 // m_addContainerButton->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    QObject::connect(m_addContainerButton, SIGNAL(clicked()), this, SLOT(startAddContainer()));

    setLayout(new QVBoxLayout);
    m_containersWidget->setLayout(new QVBoxLayout);
    m_containersWidget->layout()->setContentsMargins(0, 0, 0, 0);
 // this->setStyleSheet("ConfiguratorWindow > QWidget { margin-left: -10px; }");
    layout()->addWidget(m_containersWidget);
    layout()->addWidget(m_addContainerButton);

    loadFromFile(m_device);
}

void ConfiguratorWindow::loadFromFile(AndroidDevice *device) {
    m_containersWidget->layout()->addWidget(new ContainerWidget(m_device, "Android 1", this)); //, 1, Qt::AlignLeft);

    QFile file(m_storageFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {

        // ?

        line = in.readLine();
    }
    file.close(); // when your done.
}

void ConfiguratorWindow::startAddContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(m_device, this);
    QObject::connect(dialog, SIGNAL(accepted()), this, SLOT(addContainerWidget()));
    dialog->show();
}

void ConfiguratorWindow::addContainerWidget() {
    m_containersWidget->layout()->addWidget(new ContainerWidget(m_device, "Android 1", this)); //, 1, Qt::AlignLeft);
//    cont->updateGeometry();
//    cont->update();
//    cont->layout()->update();
//    m_containerListLayout->update();
//    layout()->update();
//    updateGeometry();
//    update();
}

