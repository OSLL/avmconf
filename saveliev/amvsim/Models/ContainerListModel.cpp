#include <stdexcept>
#include <algorithm>
#include <QDebug>
#include <QVariant>
#include <QSize>

#include "ContainerListModel.h"
#include "../api/ContainerInfo.h"

ContainerListModel::ContainerListModel(IDevice* device, QObject* parent) :
    QAbstractListModel(parent),
    m_device(device)
{
    std::vector<std::string> ids = device->getContainersIds();
    for (int i = 0; i != ids.size(); ++i) {
        m_ids.push_back(QString::fromStdString(ids[i]));
    }
}


QVariant ContainerListModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.row() < m_ids.size()) {
            return m_ids[index.row()];
        } else {
            qDebug() << "ContainerListModel::data. Out of range: row =" << index.row();
            return QVariant();
        }
    }

    if (role == Qt::SizeHintRole) {
        return QSize(0, 50);
    }

    return QVariant();

     // QVariant var;
     // var.setValue<ContainerInfo>(m_device->getContainerInfoAt(index.row()));
     // return var;
}


int ContainerListModel::rowCount(const QModelIndex&) const
{
    return m_ids.size();
}


int ContainerListModel::columnCount(const QModelIndex&) const
{
    return 1;
}


int ContainerListModel::createContainer(const QString& name, StorageDescriptor& descriptor)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    
    IDevice::Result result = m_device->createContainer(name.toStdString(), descriptor);

    if (result == IDevice::CannotSave) {
        qDebug() << "DeviceModel: Error creating container " << name << ": cannot save containers to file";
    }
    else if (result == IDevice::CannotLoadImage) {
        qDebug() << "DeviceModel: Error creating container " << name << ": cannot load image";
    }
    else if (result == IDevice::IdAlreadyExists) {
        qDebug() << "DeviceModel: Error creating container " << name << ": container with such id already exists";
    }
    else if (result == IDevice::Alright) {
        m_ids.push_back(name);
      //  emit(layoutChanged());
      //  emit(created(name)); //? m_device->getContainerInfo(name.toStdString())))
    } else {
        qDebug() << "DeviceModel: Unknown error creating container " << name;
    }
    
    endInsertRows();
    
    return 0;
}


int ContainerListModel::destroyContainer(const QString& name)
{
    beginRemoveRows(QModelIndex(), getRow(name), getRow(name));

    IDevice::Result result = m_device->destroyContainer(name.toStdString());

    if (result == -1) {
        qDebug() << "Error destroying container: not container with name " << name;
    }
    else if (result < 0) {
        qDebug() << "Unknown error destroying container " << name;
    }
    else if (result >= 0) {
        m_ids.erase(std::find(m_ids.begin(), m_ids.end(), name));
        emit(layoutChanged());
    }

    endRemoveRows();

    return 0;
}


int ContainerListModel::switchToContainer(const QString& name)
{
    return m_device->switchToContainer(name.toStdString());
}


int ContainerListModel::startContainer(const QString& name)
{
    return m_device->startContainer(name.toStdString());
}


int ContainerListModel::stopContainer(const QString& name)
{
    return m_device->stopContainer(name.toStdString());
}


ContainerInfo ContainerListModel::getContainerInfo(const QString& name)
{
    return m_device->getContainerInfo(name.toStdString());
}


int ContainerListModel::getRow(const QString& name) const
{
    int row = -1;
    for (int i = 0; i != m_ids.size(); ++i) {
        if (name == m_ids[i]) {
            row = i;
        }
    }

    return row;
}

const std::vector<Parameter*> &ContainerListModel::getContainerParametersList() const
{
    return m_device->getContainerParametersList();
}


//bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role) {
//    int row = index.row();

//    this->insertRow()
//    ContainerInfo contInfo =

//    m_device->createContainer(p.first  .toString(), );

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

