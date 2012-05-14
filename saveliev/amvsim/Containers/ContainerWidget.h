#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include <QItemDelegate>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

#include "../api/ContainerInfo.h"
#include "ContainerListModel.h"

class ContainerWidget : public QWidget {
    Q_OBJECT

private:
    QString m_contName;
    ContainerListModel *m_model;

    QPushButton *m_powerButton;
    QLabel *m_nameLabel;
    QPushButton *m_switchButton;

    QPushButton *m_destroyButton;
    
    QVector<QPushButton*> *m_switchButtons;

    void highlightAsActive();

public:
    ContainerWidget(QVariant contName, QAbstractItemModel* model, QWidget *parent, QVector<QPushButton*> *switchButtons);
 // void start();
 // void stop();
    void mousePressEvent(QMouseEvent*);
    
signals:
    void pressed(const QString& m_contName);

public slots:    
    void powerPressed();
    void switchHerePressed();
    void destroyContainer();
};

#endif // CONTAINEREDITDELEGATE_H







