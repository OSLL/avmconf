#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include "api/ContainerInfo.h"
#include "device-model.h"
#include <QItemDelegate>
#include <QPushButton>
#include <QLabel>

class ContainerWidget : public QWidget {
    Q_OBJECT

private:
    QString m_contName;
    DeviceModel *m_model;

    QPushButton *m_powerButton;
    QLabel *m_nameLabel;
    QPushButton *m_switchButton;

    void highlightAsActive();

public:
    ContainerWidget(QString contName, DeviceModel* model, QObject *parent);
//    void start();
//    void stop();

signals:

public slots:    
    void powerPressed();
    void switchHerePressed();
};

#endif // CONTAINEREDITDELEGATE_H
