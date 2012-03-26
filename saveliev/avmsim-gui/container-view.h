#ifndef CONTAINERVIEW_H
#define CONTAINERVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "api/AndroidDevice.h"

class ContainerView : public QWidget {
    Q_OBJECT
    QLineEdit *nameEdit;
    QLabel *nameLabel;
    QPushButton *startButton;
    QPushButton *stopButton;

    AndroidDevice *device;
    Container *container;

public:
    explicit ContainerView(AndroidDevice *device, const std::string &containerName, QWidget *parent = 0);

signals:

public slots:
    void setName();
    void stop();
    void start();
};

#endif // CONTAINERVIEW_H
