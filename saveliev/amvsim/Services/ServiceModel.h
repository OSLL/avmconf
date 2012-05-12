#ifndef SERVICEMODEL_H
#define SERVICEMODEL_H

#include <vector>
#include <QString>
#include <QAbstractListModel>

#include "ServiceListModel.h"

class ServiceModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    ServiceModel(const QString &serviceId, ServiceListModel *serviceListModel, QObject *parent = 0);    
    
    QVariant headerData(int section, Qt::Orientation, int role) const;
    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int getRow(const QString& id) const;
    
    Parameter *getParameter(QVariant id) const;
    
private:
    ServiceInfo m_serviceInfo;
    ServiceListModel *m_serviceListModel;
    std::vector<QString> m_parameterIds;
    
signals:
    
public slots:
    
};

#endif // SERVICEMODEL_H
