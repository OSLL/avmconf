#include <QVBoxLayout>
#include <QScrollArea>

#include "MainWindow.h"
#include "Dialogs/NewContainerDialog.h"
#include "Elements/ErrorLabel.h"
#include "ContainerList/ContainerWidget.h"
#include <Dialogs/DeviceParametersDialog.h>

#ifdef SMARTPHONE
#include <QWSServer>
#include <QThread>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTimer>

#include "SupervisorListener.h"
#endif

#ifdef SMARTPHONE

static QString findBacklightControl() {
    QDir bd("/sys/class/backlight");
    if (bd.exists()) {
	QString brd;
	foreach (brd, bd.entryList()) {
	    if (brd.startsWith(".")) {
		continue;
	    }

	    QFile br(bd.absolutePath() + "/" + brd + "/brightness");
	    if (br.exists()) {
		qDebug() << "Backlight control is at " << br.fileName();
		return br.fileName();
	    }	    
	}
    } else {
	qDebug() << "No backlight class\n";
    }

    return QString();
}
#endif

MainWindow::MainWindow(IDevice* device, QWidget* parent)
    : QMainWindow(parent), m_device(device)
{    
    setWindowTitle("Configurator");

#if defined(DESKTOP)

    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    setFixedHeight(HEIGHT);
    setFixedWidth(WIDTH);

#elif defined(SMARTPHONE)

    bf = findBacklightControl();
    workaroundStartupCounter = 0;
    
    setStyleSheet(" QWidget { font-family: sans-serif; font-size: 9px; }");
    //setFont(QFont("sans", 9));

#endif
    
    QWidget *allWidget = new QWidget;
    allWidget->setLayout(new QVBoxLayout);
    allWidget->layout()->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(allWidget);
        
    QWidget *containersWidget = initContainerList();
    QWidget *buttons = initButtons();
            
    ((QVBoxLayout*)allWidget->layout())->addWidget(containersWidget);
    ((QVBoxLayout*)allWidget->layout())->addWidget(buttons);
    
    setTabOrder(containersWidget, buttons);

#ifdef SMARTPHONE
    SupervisorListener* sl = new SupervisorListener();
    connect(sl, SIGNAL(switchedToRoot()), this, SLOT(doRepaint()));
    connect(sl, SIGNAL(phoneAdded()), this, SLOT(preventBlanking()));
    sl->start();
    lightUp();

    QTimer* waTimer = new QTimer(this);
    waTimer->setInterval(3000);
    waTimer->start(3000);
    connect(waTimer, SIGNAL(timeout()), this, SLOT(workaround()));
#endif
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


#ifdef SMARTPHONE

void MainWindow::doRepaint() {
    QWSServer* s = QWSServer::instance();

    if (s) {
	s->refresh();
    }

    lightUp();
}

void MainWindow::preventBlanking() {
    workaroundStartupCounter = 6;
}

void MainWindow::workaround() {
    // Android startup screen blanking workaround

    if (workaroundStartupCounter > 0) {
	qDebug() << "Refreshing screen...";
	doRepaint();
	workaroundStartupCounter--;
	return;
    }

    // Fix backlight

    if (!bf.isEmpty()) {
	QFile brc(bf);

	if (brc.open(QIODevice::ReadWrite | QIODevice::Unbuffered)) {
	    if (brc.read(3).toInt() == 0) {
		qDebug() << "Turning backlight on";
		brc.write("100");
	    }
	} else {
	    qDebug() << "Failed to read " << brc.fileName();
	}
    }    
}

void MainWindow::lightUp() {
    QFile brc(bf);

    if (brc.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
	brc.write("100");
    } else {
	qDebug() << "Failed to write to " << brc.fileName();
    }
}

#endif



