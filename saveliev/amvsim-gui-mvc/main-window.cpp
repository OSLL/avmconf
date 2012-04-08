#include "mainwindow.h"
#include "container-edit-delegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    setWindowTitle("Configurator");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    setLayout(new QVBoxLayout());

    m_view = new QListView(this);
    m_model = new DeviceModel(this);
    m_view->setModel(m_model);
    //m_view->setItemDelegate();

    ContainerEditDelegate *delegate = new ContainerEditDelegate(this);
    m_view->setItemDelegate(delegate);

    //item->setFlags( item->flags() & ~Qt::ItemIsSelectable );

    m_createButton = new QPushButton("Create new container", this);
    connect(m_createButton, SIGNAL(clicked()), m_model, SLOT(createContainer()));

    layout()->addWidget(m_view);
    layout()->addWidget(m_createButton);

    m_view->setEditTriggers(QAbstractItemView::DoubleClicked);

    m_view->viewport()->setAttribute(Qt::WA_Hover);

//    connect(m_view->, SIGNAL(item))
//    for (QList<QObject*>::const_iterator it = m_view->children().begin(); it != m_view->children().end(); ++it) {
//        connect(*it, SIGNAL(doubleClicked(QModelIndex)), m_view, SLOT(edit(QModelIndex)));
//    }
}
