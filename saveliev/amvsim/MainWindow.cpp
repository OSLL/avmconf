#include <QVBoxLayout>
#include <QScrollArea>

#include "MainWindow.h"
#include "Dialogs/NewContainerDialog.h"
#include "Elements/ErrorLabel.h"
#include "Views/ContainerWidget.h"

MainWindow::MainWindow(IDevice* device, QWidget* parent)
    : QMainWindow(parent), m_device(device)
{    
    setWindowTitle("Configurator");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    setFixedHeight(HEIGHT);
    setFixedWidth(WIDTH);
    setStyleSheet("font-size: 13px");
    
    QWidget *allWidget = new QWidget;
    allWidget->setLayout(new QVBoxLayout);
    allWidget->layout()->setContentsMargins(10, 10, 10, 10);
    setCentralWidget(allWidget);
        
    QWidget *containersWidget = initContainerList();
    QWidget *parametersWidget = initDeviceParameters();
        
    QScrollArea *sa = new QScrollArea();
    sa->setWidget(parametersWidget);
    
    ((QVBoxLayout*)allWidget->layout())->addWidget(m_createContainerButton, 0, Qt::AlignLeft);
    ((QVBoxLayout*)allWidget->layout())->addWidget(containersWidget);
    ((QVBoxLayout*)allWidget->layout())->addWidget(sa);
}

QWidget *MainWindow::initContainerList()
{
    m_containersModel = new ContainerListModel(m_device, this);
    
    m_containersView = new ContainerListView(this);
    m_containersView->setModel(m_containersModel);
    m_createContainerButton = new QPushButton("Create new container", this);
    QObject::connect(m_createContainerButton, SIGNAL(clicked()), this, SLOT(startAddingContainer()));
    
    QWidget *w = new QWidget;
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 10);
    w->setFixedHeight(CONTAINERLIST_HEIGHT);        
    w->layout()->addWidget(m_containersView);
    
    return w;
}

QWidget * MainWindow::initDeviceParameters()
{
    QWidget *w = new QWidget;
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    
    w->layout()->addWidget(new QLabel("Device parameters"));
    ((QVBoxLayout*)w->layout())->addWidget(new ParametersWidget(m_device,
            m_device->getDeviceParametersList()), 0, Qt::AlignTop); 
    
    return w;    
}

void MainWindow::startAddingContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(this, m_containersModel);
    dialog->show();
}

