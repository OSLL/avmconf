#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "api/AndroidDevice.h"
#include "Containers/ContainerListModel.h"
#include "Containers/ContainerListView.h"
#include "Services/ServiceListModel.h"
#include "Services/ServiceListView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AndroidDevice* device, QWidget* parent = 0);

private:
    ContainerListModel *m_containersModel;
    ContainerListView *m_containersView;
    ServiceListModel *m_servicesModel;
    ServiceListView *m_servicesView;
    QPushButton *m_createContainerButton;
    QLabel *m_errorLabel;
    
public slots:
    void startAddingContainer();
};

#endif // MAINWINDOW_H
