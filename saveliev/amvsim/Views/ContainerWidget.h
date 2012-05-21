#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include <QItemDelegate>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

#include "ContainerListView.h"
#include "../api/ContainerInfo.h"
#include "../Models/ContainerListModel.h"

class ContainerWidget : public QWidget {
    Q_OBJECT

private:
    QString m_contName;
    ContainerListModel *m_model;

    QPushButton *m_powerButton;
    QLabel *m_nameLabel;
    QPushButton *m_switchButton;
    
    QMap<QString, ContainerWidget*> *m_anotherContainerWidgets;

    void highlightTheRestRunningAsInactive();
    void highlightAsActive();
    void highlightAsStopped();
    void highlightRunningAsInactive();
    
public:
    ContainerWidget(QVariant contName, QAbstractItemModel* model, QWidget *parent, 
                    QMap<QString, ContainerWidget*> *anotherContainerWidgets);
    
    void mousePressEvent(QMouseEvent*);
    
signals:
    void pressed(const QString& m_contName);

public slots:    
    void powerPressed();
    void switchHerePressed();
};

#endif // CONTAINEREDITDELEGATE_H







