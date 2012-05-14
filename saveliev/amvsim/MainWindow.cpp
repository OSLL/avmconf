#include <QVBoxLayout>

#include "MainWindow.h"
#include "Containers/NewContainerDialog.h"
#include "ErrorLabel.h"
#include "Containers/ContainerWidget.h"
#include "Services/ContainerParametersWidget.h"

MainWindow::MainWindow(AndroidDevice* device, QWidget* parent)
    : QMainWindow(parent)
{
    const int HEIGHT = 600;
    const int LISTWIDTH = 450;
    const int OPTIONSWIDTH = 350;
    
    setWindowTitle("Configurator");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    setFixedHeight(HEIGHT);
    
    QWidget *allWidget = new QWidget;
    allWidget->setLayout(new QHBoxLayout);
    allWidget->layout()->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(allWidget);
    
    
    // CONTAINERS LIST
    m_containersModel = new ContainerListModel(device, this);
    
    QWidget *leftWidget = new QWidget;
    leftWidget->setLayout(new QVBoxLayout);
    leftWidget->setFixedWidth(LISTWIDTH);
    leftWidget->layout()->setContentsMargins(12, 12, 0, 12);
    allWidget->layout()->addWidget(leftWidget);
    
    m_containersView = new ContainerListView(this);
    m_containersView->setModel(m_containersModel);
    m_createContainerButton = new QPushButton("Create new container", this);
    QObject::connect(m_createContainerButton, SIGNAL(clicked()), this, SLOT(startAddingContainer()));
    leftWidget->layout()->addWidget(m_containersView);
    leftWidget->layout()->addWidget(m_createContainerButton);
    
    
    // SERVICES    
    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(new QVBoxLayout);
    rightWidget->setFixedWidth(OPTIONSWIDTH);
    rightWidget->layout()->setContentsMargins(0, 12, 12, 12);
    allWidget->layout()->addWidget(rightWidget);
    
    rightWidget->layout()->addWidget(new ContainerParametersWidget(device));
            
//  m_containerParametersView = new 
    
//  m_servicesModel = new ServiceListModel(device, this);    
//  m_servicesView = new ServiceListView(this);
//  m_servicesView->setModel(m_servicesModel);
//  m_servicesView->setLayout(new QVBoxLayout);
//  rightWidget->layout()->addWidget(m_servicesView);
    
    
 // item->setFlags( item->flags() & ~Qt::ItemIsSelectable );

//    m_view->setEditTriggers(QAbstractItemView::DoubleClicked);
//    m_view->viewport()->setAttribute(Qt::WA_Hover);

//    connect(m_view->, SIGNAL(item))
//    for (QList<QObject*>::const_iterator it = m_view->children().begin(); it != m_view->children().end(); ++it) {
//        connect(*it, SIGNAL(doubleClicked(QModelIndex)), m_view, SLOT(edit(QModelIndex)));
//    }
}

void MainWindow::startAddingContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(this, m_containersModel);
    dialog->show();
}
