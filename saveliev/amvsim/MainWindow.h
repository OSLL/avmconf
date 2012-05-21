#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "api/IDevice.h"
#include "Models/ContainerListModel.h"
#include "Views/ContainerListView.h"
#include "Views/ParametersWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IDevice* device, QWidget* parent = 0);

private:
    static const int HEIGHT = 600;
    static const int CONTAINERLIST_HEIGHT = 350;
    static const int WIDTH = 480;
    
    IDevice *m_device;
    ContainerListModel *m_containersModel;
    ContainerListView *m_containersView;
    QPushButton *m_createContainerButton;
    QLabel *m_errorLabel;
    
    QWidget *initContainerList();
    QWidget *initDeviceParameters();
    
public slots:
    void startAddingContainer();
};

#endif // MAINWINDOW_H
