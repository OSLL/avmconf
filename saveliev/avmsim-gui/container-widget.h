#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "api/AndroidDevice.h"

class ContainerWidget : public QWidget {
    Q_OBJECT

    QLabel *m_nameLabel;
    QLineEdit *m_nameEdit;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;

    AndroidDevice *m_device;

public:
    explicit ContainerWidget(AndroidDevice *device, QString containerName, QWidget *parent = 0);

signals:

public slots:
    void stop();
    void start();
    void setName();
    void changeName();
};

#endif // CONTAINERWIDGET_H
