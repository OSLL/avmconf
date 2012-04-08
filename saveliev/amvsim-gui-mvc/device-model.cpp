#include "device-model.h"

#include <QVariant>

DeviceModel::DeviceModel(QObject *parent) : QAbstractListModel(parent) {
    m_device.createContainer("Android VM");
    m_device.createContainer("Android VM");
    m_device.createContainer("Android VM");
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return QString::fromStdString(m_device.getContainers()[index.row()]->getName());
    }
    return QVariant();
}

int DeviceModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_device.getContainers().size();
}

int DeviceModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

void DeviceModel::createContainer() {
    m_device.createContainer("Android created");
    emit(layoutChanged());
}

//QModelIndex DeviceModel::index(int row, int column, const QModelIndex &parent) const {
//}

//QModelIndex DeviceModel::parent(const QModelIndex &child) const {
//}
