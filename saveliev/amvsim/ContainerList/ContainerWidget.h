#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include <QItemDelegate>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QToolButton>

#include "ContainerListView.h"
#include "ContainerListModel.h"
#include "api/ContainerInfo.h"
#include "PowerButton.h"
#include "SwitchButton.h"

class ContainerWidget : public QWidget {
    Q_OBJECT

private:
    QString m_contName;
    ContainerListModel *m_model;

    TextPowerButton *m_powerButton;
    QLabel *m_nameLabel;
    SwitchButton *m_switchButton;
    
    QMap<QString, ContainerWidget*> *m_anotherContainerWidgets;

    void highlightAsRunning();
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
    void switchPressed();
};

#endif // CONTAINEREDITDELEGATE_H







