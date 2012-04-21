#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include "api/ContainerInfo.h"
#include "DeviceModel.h"
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

    QPushButton *m_destroyButton;

    void highlightAsActive();

public:
    ContainerWidget(QString contName, DeviceModel* model, QWidget *parent);
 // void start();
 // void stop();

signals:

public slots:    
    void powerPressed();
    void switchHerePressed();
    void destroyContainer();
};

#endif // CONTAINEREDITDELEGATE_H
