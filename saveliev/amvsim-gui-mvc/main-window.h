#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>

#include "device-model.h"
#include "container-delegate.h"
#include "containers-list-view.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    DeviceModel *m_model;
    ContainersListView *m_view;
    QPushButton *m_createContainerButton;

public slots:
    void startAddingContainer();
 // void finishAddingContainer(ContainerInfo);
};

#endif // MAINWINDOW_H
