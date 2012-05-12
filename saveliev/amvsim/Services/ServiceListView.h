#ifndef SERVICESLISTVIEW_H
#define SERVICESLISTVIEW_H

#include <QListView>

#include "ServiceListModel.h"

class ServiceListView : public QListView
{
    Q_OBJECT
public:
    explicit ServiceListView(QWidget *parent = 0);    
    virtual void setModel(ServiceListModel *model);

private:
    void setWidgets(int start, int end);
    
public slots:
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);  
};

#endif // SERVICESLISTVIEW_H
