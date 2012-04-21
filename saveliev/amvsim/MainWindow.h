#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "api/AndroidDevice.h"
#include "DeviceModel.h"
#include "ContainersListView.h"
#include "ContainerDelegate.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AndroidDevice* device, QWidget* parent = 0);

private:
    DeviceModel *m_model;
    ContainersListView *m_view;
    QLabel *m_errorLabel;
    QPushButton *m_createContainerButton;

public slots:
    void startAddingContainer();
 // void finishAddingContainer(ContainerInfo);
};

#endif // MAINWINDOW_H
