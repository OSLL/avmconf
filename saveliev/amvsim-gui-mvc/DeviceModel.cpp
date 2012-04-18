
#include <stdexcept>

#include <QDebug>
#include <QVariant>
#include <QSize>
#include "DeviceModel.h"
#include "api/ContainerInfo.h"

DeviceModel::DeviceModel(QObject *parent) : QAbstractListModel(parent) {
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        try {            
            return QString::fromStdString(m_device.getContainerNameAt(index.row()));
         // QVariant var;
         // var.setValue<ContainerInfo>(m_device.getContainerInfoAt(index.row()));
         // return var;            
        } catch (std::out_of_range e) {
            qDebug() << "Out of range: row =" << index.row();
            return QVariant();
        }
    }

    if (role == Qt::SizeHintRole) {
        return QSize(300, 50);
    }

    return QVariant();
}

int DeviceModel::rowCount(const QModelIndex &) const {
    return m_device.getContainersNumber();
}

int DeviceModel::columnCount(const QModelIndex &) const {
    return 1;
}

int DeviceModel::createContainer(QString name, StorageDescriptor descriptor) {
    int result = m_device.createContainer(name.toStdString(), descriptor);

    switch (result) {
    case -1:
        qDebug() << "Error creating container: container with such name already exists";
        break;
    case -2:
        qDebug() << "Error creating container: cannot load image";
        break;
    case -3:
        qDebug() << "Error creating container: cannot open file to save";
        break;
    default:
        emit(layoutChanged());
        emit(created(name)); //m_device.getContainerInfo(name.toStdString())));
    }

    return result;
}

int DeviceModel::destroyContainer(QString name) {
    qDebug() << "destroyContainer: rowCount = " << rowCount();
    if (m_device.destroyContainer(name.toStdString()) >= 0) {
        qDebug() << "destroyContainer: rowCount = " << rowCount();
        emit(layoutChanged());
        emit(dataChanged(index(0, 0), index(rowCount()-2, 0)));
        return 0;
    }
    return -1;
}

int DeviceModel::switchToContainer(QString name) {
    m_device.switchToContainer(name.toStdString());
}

int DeviceModel::startContainer(QString name) {
    m_device.startContainer(name.toStdString());
}

int DeviceModel::stopContainer(QString name) {
    m_device.stopContainer(name.toStdString());
}

ContainerInfo DeviceModel::getContainerInfo(QString name) {
    return m_device.getContainerInfo(name.toStdString());
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
