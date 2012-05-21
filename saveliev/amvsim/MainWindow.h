#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "api/IDevice.h"
#include "ContainerList/ContainerListModel.h"
#include "ContainerList/ContainerListView.h"
#include "ParameterWidgets/ParametersWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IDevice* device, QWidget* parent = 0);

private:
    static const int HEIGHT = 600;
    static const int WIDTH = 480;
    
    IDevice *m_device;
    ContainerListModel *m_containersModel;
    ContainerListView *m_containersView;
    QPushButton *m_createContainerButton;
    QPushButton *m_callParametersDialogButton;
    QLabel *m_errorLabel;
    
    QWidget *initContainerList();
    QWidget *initButtons();
    
public slots:
    void startAddingContainer();
    void openParametersDialog();
};

#endif // MAINWINDOW_H
