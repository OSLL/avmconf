#ifndef CONTAINERSLISTVIEW_H
#define CONTAINERSLISTVIEW_H

#include <QListView>
#include <QButtonGroup>

class ContainerWidget;

class ContainerListView : public QListView 
{
    Q_OBJECT

public:
    explicit ContainerListView(QWidget *parent = 0);
    virtual void setModel(QAbstractItemModel * model);
    
private:
    void setWidgets(int start, int end);
    
    QMap<QString, ContainerWidget*> m_containerWidgets;
    
    int m_selected;   
    

public slots:
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
    virtual void itemPressed(const QString& contName);
};

#endif // CONTAINERSLISTVIEW_H
