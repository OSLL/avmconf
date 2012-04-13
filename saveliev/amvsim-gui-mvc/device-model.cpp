#include <stdexcept>
#include <QVariant>
#include <QSize>
#include <iostream>
#include "device-model.h"
#include "api/container-info.h"

DeviceModel::DeviceModel(QObject *parent) : QAbstractListModel(parent) {
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const {
//    if (role == Qt::DisplayRole) {
//        try {
//            return QString::fromStdString(m_device.getContainerInfoAt(index.row()));
//        } catch (std::out_of_range e) {
//            return QVariant();
//        }
//    }
    if (role == Qt::SizeHintRole) {
        return QSize(300, 50);
    }

    return QVariant();
}

int DeviceModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_device.getContainersNumber();
}

int DeviceModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

bool DeviceModel::createContainer(QString name, StorageDescriptor descriptor) {
    if(m_device.createContainer(name.toStdString(), descriptor) >= 0) {
        emit(layoutChanged());
        emit(created(m_device.getContainerInfo(name.toStdString())));
        return true;
    }
    return false;
}

//bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role) {
//    int row = index.row();

//    this->insertRow()
//    ContainerInfo contInfo =

//    m_device.createContainer(p.first  .toString(), );

//    if (index.column() == 0)
//        p.first = value.toString();
//    else if (index.column() == 1)
//        p.second = value.toString();
//    else
//        return false;

//    listOfPairs.replace(row, p);
//    emit(dataChanged(index, index));

//    return true;
//}

//QModelIndex DeviceModel::index(int row, int column, const QModelIndex &parent) const {
//}

//QModelIndex DeviceModel::parent(const QModelIndex &child) const {
//}
