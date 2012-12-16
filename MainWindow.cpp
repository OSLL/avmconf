/* -*- c-basic-offset: 4 -*- */

#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QWSServer>
#include <QThread>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "MainWindow.h"
#include "Dialogs/NewContainerDialog.h"
#include "Elements/ErrorLabel.h"
#include "Views/ContainerWidget.h"

#include "SupervisorListener.h"

// ================================================================================

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


MainWindow::MainWindow(IDevice* device, QWidget* parent)
    : QMainWindow(parent)
{
    /*
    const int HEIGHT = 600;
    const int LISTWIDTH = 480;
    const int OPTIONSWIDTH = 0;
    */

    m_wpaGui = 0;

    bf = findBacklightControl();
    workaroundStartupCounter = 0;
    fixBacklight = true;

    setFont(QFont("sans", 9));
    
    setWindowTitle("Configurator");
    //setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    //setFixedHeight(HEIGHT);
    //setStyleSheet("font-size: 13px");
    
    QWidget *allWidget = new QWidget;
    allWidget->setLayout(new QHBoxLayout);
    allWidget->layout()->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(allWidget);
    
    
    // CONTAINERS LIST
    m_containersModel = new ContainerListModel(device, this);
    
    QWidget *leftWidget = new QWidget;
//    leftWidget->setLayout(new QGridLayout);
//    leftWidget->setFixedWidth(LISTWIDTH);
//    leftWidget->layout()->setContentsMargins(5, 5, 5, 5);

    
    m_containersView = new ContainerListView(this);
    m_containersView->setModel(m_containersModel);
    m_createContainerButton = new QPushButton("Create new container", this);
    connect(m_createContainerButton, SIGNAL(clicked()), this, SLOT(startAddingContainer()));

    m_callWpaGui = new QPushButton("Configure WiFi", this);
    connect(m_callWpaGui, SIGNAL(clicked()), this, SLOT(showWpaGui()));

    QGridLayout *leftWidgetLayout = new QGridLayout();
    leftWidgetLayout->setContentsMargins(5, 5, 5, 5);
    leftWidgetLayout->addWidget(m_containersView, 0, 0, 1, 2);
    leftWidgetLayout->addWidget(m_createContainerButton, 1, 0);
    leftWidgetLayout->addWidget(m_callWpaGui, 1, 1);
    leftWidgetLayout->setRowStretch(0, 1);
    leftWidget->setLayout(leftWidgetLayout);
    allWidget->layout()->addWidget(leftWidget);

//    leftWidget->layout()->addWidget(m_containersView);
//    leftWidget->layout()->addWidget(m_createContainerButton);

    SupervisorListener* sl = new SupervisorListener();
    connect(sl, SIGNAL(switchedToRoot()), this, SLOT(switchedToRoot()));
    connect(sl, SIGNAL(phoneAdded()), this, SLOT(preventBlanking()));
    connect(sl, SIGNAL(switchedToContainer()), this, SLOT(switchedToContainer()));
    sl->start();
    lightUp();

    
    QTimer* waTimer = new QTimer(this);
    waTimer->setInterval(3000);
    waTimer->start(3000);
    connect(waTimer, SIGNAL(timeout()), this, SLOT(workaround()));
    
//    // SERVICES    
//    QWidget *rightWidget = new QWidget;
//    rightWidget->setLayout(new QVBoxLayout);
//    rightWidget->setFixedWidth(OPTIONSWIDTH);
//    rightWidget->layout()->setContentsMargins(0, 12, 12, 12);
//    allWidget->layout()->addWidget(rightWidget);
    
//    rightWidget->layout()->addWidget(new ContainerParametersWidget(device));
            
    
    
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
void MainWindow::showWpaGui() {
    if(m_wpaGui) delete m_wpaGui;
    m_wpaGui = new WpaGui(this);
    m_wpaGui->show();
}

void MainWindow::startAddingContainer() {
    NewContainerDialog *dialog = new NewContainerDialog(this, m_containersModel);
    dialog->show();
}

static void fixPowerState() {
    QFile sysPowerState("/sys/power/state");

    qDebug() << "Updating power state...";

    if (sysPowerState.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
	sysPowerState.write("on");
    } else {
	qDebug() << "Failed to write to " << sysPowerState.fileName();
    }
    
    qDebug() << "Done updating power state";
}

void MainWindow::switchedToRoot() {
    fixBacklight = true;
    doRepaint();

    QFile fbpan("/sys/class/graphics/fb0/pan");
    if (fbpan.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
	fbpan.write("0,0");
    } else {
	qDebug() << "Failed to pan the framebuffer!";
    }
}

void MainWindow::doRepaint() {
//    QWSServer* s = QWSServer::instance();

//    if (s) {
//	s->refresh();
//    }

    lightUp();
    fixPowerState();
}

void MainWindow::switchedToContainer() {
    fixBacklight = false;
}

void MainWindow::preventBlanking() {
    workaroundStartupCounter = 6;
}

void MainWindow::workaround() {
    // Android startup screen blanking workaround

    if (workaroundStartupCounter > 0) {
	qDebug() << "Refreshing screen...";

	if (fixBacklight) {
	    doRepaint();
	}

	workaroundStartupCounter--;
	return;
    }

    // Fix backlight

    if (!bf.isEmpty() && fixBacklight) {
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
