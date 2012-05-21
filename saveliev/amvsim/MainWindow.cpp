#include <QVBoxLayout>
#include <QScrollArea>

#include "MainWindow.h"
#include "Dialogs/NewContainerDialog.h"
#include "Elements/ErrorLabel.h"
#include "Views/ContainerWidget.h"
#include <Dialogs/DeviceParametersDialog.h>

MainWindow::MainWindow(IDevice* device, QWidget* parent)
    : QMainWindow(parent), m_device(device)
{    
    setWindowTitle("Configurator");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    setFixedHeight(HEIGHT);
    setFixedWidth(WIDTH);
    setStyleSheet("font-size: 13px;");
    
    QWidget *allWidget = new QWidget;
    allWidget->setLayout(new QVBoxLayout);
    allWidget->layout()->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(allWidget);
        
    QWidget *containersWidget = initContainerList();
    QWidget *buttons = initButtons();
            
    ((QVBoxLayout*)allWidget->layout())->addWidget(containersWidget);
    ((QVBoxLayout*)allWidget->layout())->addWidget(buttons);
    
    setTabOrder(containersWidget, buttons);
}

QWidget *MainWindow::initContainerList()
{
    m_containersModel = new ContainerListModel(m_device, this);    
    m_containersView = new ContainerListView(this);
    m_containersView->setModel(m_containersModel);
    
    QWidget *w = new QWidget;
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);     
    w->layout()->addWidget(m_containersView);
    
    return w;
}

QWidget * MainWindow::initButtons()
{
    m_createContainerButton = new QPushButton("Create new container", this);
    QObject::connect(m_createContainerButton, SIGNAL(clicked()), this, SLOT(startAddingContainer()));
    
    m_callParametersDialogButton = new QPushButton("Change device parameters");
    QObject::connect(m_callParametersDialogButton, SIGNAL(clicked()), this, SLOT(openParametersDialog()));
    
    QWidget *w = new QWidget;
    w->setLayout(new QHBoxLayout);  
    ((QHBoxLayout*)w->layout())->setContentsMargins(15, 0, 15, 15);
    ((QHBoxLayout*)w->layout())->addWidget(m_createContainerButton, 0, Qt::AlignLeft);  
    ((QHBoxLayout*)w->layout())->addWidget(m_callParametersDialogButton, 0, Qt::AlignRight); 
    
    return w;    
}

void MainWindow::startAddingContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(this, m_containersModel);
    dialog->show();
}

void MainWindow::openParametersDialog()
{
    DeviceParametersDialog *dialog = new DeviceParametersDialog(m_device);
    dialog->show();
}






