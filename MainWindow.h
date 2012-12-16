#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "api/IDevice.h"
#include "Models/ContainerListModel.h"
#include "Views/ContainerListView.h"
#include "WPA/wpagui.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IDevice* device, QWidget* parent = 0);

private:
    ContainerListModel *m_containersModel;
    ContainerListView *m_containersView;
    QPushButton *m_createContainerButton;
    QPushButton *m_callWpaGui;
    QLabel *m_errorLabel;
    WpaGui *m_wpaGui;

private:
    QString bf;
    int workaroundStartupCounter;
    bool fixBacklight;

    void lightUp();
    void doRepaint();
    
public slots:
    void startAddingContainer();
    void switchedToRoot();
    void switchedToContainer();

private slots:
    void showWpaGui();
    void preventBlanking();
    void workaround();
};

#endif // MAINWINDOW_H
