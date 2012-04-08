#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QListView>
#include <QPushButton>

#include "device-model.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DeviceModel *m_model;
    QListView   *m_view;
    QPushButton *m_createButton;
};

#endif // MAINWINDOW_H
