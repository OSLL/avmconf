#include <QVBoxLayout>

#include "MainWindow.h"
#include "ContainerWidget.h"
#include "NewContainerDialog.h"
#include "ContainersListView.h"
#include "ErrorLabel.h"

MainWindow::MainWindow(AndroidDevice* device, QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Configurator");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    setFixedWidth(500);
    setFixedHeight(400);

    m_view = new ContainersListView(this);
    m_model = new DeviceModel(device, this);
    m_view->setModel(m_model);
    m_view->setItemDelegate(new ContainerDelegate);

    m_errorLabel = new ErrorLabel(this);

    m_createContainerButton = new QPushButton("Create new container", this);
    QObject::connect(m_createContainerButton, SIGNAL(clicked()), this, SLOT(startAddingContainer()));

    QWidget *central = new QWidget;
    central->setLayout(new QVBoxLayout);
    central->layout()->addWidget(m_view);
 // central->layout()->addWidget(m_errorLabel);
    central->layout()->addWidget(m_createContainerButton);
    setCentralWidget(central);

 // item->setFlags( item->flags() & ~Qt::ItemIsSelectable );

//    m_view->setEditTriggers(QAbstractItemView::DoubleClicked);
//    m_view->viewport()->setAttribute(Qt::WA_Hover);

//    connect(m_view->, SIGNAL(item))
//    for (QList<QObject*>::const_iterator it = m_view->children().begin(); it != m_view->children().end(); ++it) {
//        connect(*it, SIGNAL(doubleClicked(QModelIndex)), m_view, SLOT(edit(QModelIndex)));
//    }
}

void MainWindow::startAddingContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(this, m_model);
    QObject::connect(dialog, SIGNAL(done(ContainerInfo)), this, SLOT(finishAddingContainer(ContainerInfo)));
    dialog->show();
}
