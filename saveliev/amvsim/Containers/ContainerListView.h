#ifndef CONTAINERSLISTVIEW_H
#define CONTAINERSLISTVIEW_H

#include <QListView>
#include <QButtonGroup>

#include "ContainerWidget.h"

class ContainerListView : public QListView 
{
    Q_OBJECT

public:
    explicit ContainerListView(QWidget *parent = 0);
    virtual void setModel(QAbstractItemModel * model);
    
private:
    void setWidgets(int start, int end);
    
    QVector<QPushButton*> m_switchButtons;
    
    int m_selected;   
    

public slots:
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
    virtual void itemPressed(const QString& contName);
};

#endif // CONTAINERSLISTVIEW_H
