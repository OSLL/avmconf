#include <QDebug>
#include <QSize>

#include "ServiceModel.h"

ServiceModel::ServiceModel(const QString &serviceId, ServiceListModel *serviceListModel, QObject *parent) :
    m_serviceListModel(serviceListModel), QAbstractListModel(parent)
{    
    m_serviceInfo = m_serviceListModel->getServiceInfo(serviceId);
    
    std::vector<std::string> paramIds = m_serviceInfo.getParametersIds();
    for (int i = 0; i != paramIds.size(); ++i) {
        m_parameterIds.push_back(QString::fromStdString(paramIds[i]));
    }
}


QVariant ServiceModel::headerData(int, Qt::Orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        return QString::fromStdString(m_serviceInfo.getName());
    }    
    
    if (role == Qt::SizeHintRole) {
        return QSize(0, 30);
    }
    
    return QVariant();
}


QVariant ServiceModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.row() < m_parameterIds.size()) {
            return m_parameterIds[index.row()];            
            
        } else {
            qDebug() << "ServiceModel::data. Out of range: row =" << index.row();
            return QVariant();
        }
    }

    if (role == Qt::SizeHintRole) {
        return QSize(0, 30);
    }

    return QVariant();
}


int ServiceModel::rowCount(const QModelIndex&) const
{
    return m_parameterIds.size();
}


int ServiceModel::columnCount(const QModelIndex&) const
{
    return 1;
}


Parameter *ServiceModel::getParameter(QVariant id) const
{
    return m_serviceInfo.getParameter(id.toString().toStdString());
}


int ServiceModel::getRow(const QString& id) const
{
    int row = -1;
    for (int i = 0; i != m_parameterIds.size(); ++i) {
        if (id == m_parameterIds[i]) {
            row = i;
        }
    }

    return row;
}
