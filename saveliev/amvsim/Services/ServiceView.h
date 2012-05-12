#ifndef SERVICEWIDGET_H
#define SERVICEWIDGET_H

#include <QListView>
#include <QAbstractItemModel>

#include "ServiceModel.h"

class ServiceView : public QListView
{
    Q_OBJECT
    
    QString m_serviceId;
    ServiceListModel *m_serviceListModel;
    
public:
    ServiceView(ServiceListModel* serviceListModel, QWidget *parent = 0);
    virtual void setModel(QAbstractItemModel *model);
    
private:    
    void setWidgets(int start, int end);

public slots:
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
};

#endif // SERVICEWIDGET_H
