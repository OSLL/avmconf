#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "configurator-window.h"
#include "container-view.h"
#include "new-container-dialog.h"

ConfiguratorWindow::ConfiguratorWindow(AndroidDevice *device, QWidget *parent)
    : m_device(device), QWidget(parent), m_containerListLayout(new QVBoxLayout) {

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
    layout()->addItem(m_containerListLayout);
    layout()->addWidget(m_addContainerButton);

    ContainerView *cont = new ContainerView(m_device, "Android 1", this);
    m_containerListLayout->addWidget(cont, 1, Qt::AlignLeft);
}

void ConfiguratorWindow::startAddContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(m_device, this);
    QObject::connect(dialog, SIGNAL(accepted()), this, SLOT(addContainerWidget()));
    dialog->show();
}

void ConfiguratorWindow::addContainerWidget() {
    ContainerView *cont = new ContainerView(m_device, "Android 1", this);
    m_containerListLayout->addWidget(cont, 1, Qt::AlignLeft);
    cont->updateGeometry();
    cont->update();
    m_containerListLayout->update();
    layout()->update();
    updateGeometry();
    update();
}

