
#include <stdexcept>
#include <QDebug>
#include <QVariant>
#include <QSize>

#include "ServiceListModel.h"
#include "../api/ServiceInfo.h"

ServiceListModel::ServiceListModel(AndroidDevice* device, QObject* parent) :
    QAbstractListModel(parent),
    m_device(device)
{
    std::vector<std::string> ids = device->getServicesIds();
    for (int i = 0; i != ids.size(); ++i) {
        m_serviceIds.push_back(QString::fromStdString(ids[i]));
    }
}


QVariant ServiceListModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.row() < m_serviceIds.size()) {
            return m_serviceIds[index.row()];
        } else {
            qDebug() << "ServiceListModel::data. Out of range: row =" << index.row();
            return QVariant();
        }
    }

    if (role == Qt::SizeHintRole) {
        int count = getServiceInfo(m_serviceIds.at(index.row())).getParametersCount();
        return QSize(0, count * 30);
    }

    return QVariant();
}


int ServiceListModel::rowCount(const QModelIndex&) const
{
    return m_serviceIds.size();
}


int ServiceListModel::columnCount(const QModelIndex&) const
{
    return 1;
}


ServiceInfo ServiceListModel::getServiceInfo(const QString& id) const
{
    return m_device->getServiceInfo(id.toStdString());
}


int ServiceListModel::getRow(const QString& id) const
{
    int row = -1;
    for (int i = 0; i != m_serviceIds.size(); ++i) {
        if (id == m_serviceIds[i]) {
            row = i;
        }
    }

    return row;
}
