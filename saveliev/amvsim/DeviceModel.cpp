
#include <stdexcept>

#include <QDebug>
#include <QVariant>
#include <QSize>
#include "DeviceModel.h"
#include "api/ContainerInfo.h"

DeviceModel::DeviceModel(AndroidDevice* device, QObject* parent) :
    QAbstractListModel(parent),
    m_device(device)
{
    std::vector<std::string> names = device->getContainersNames();
    for (int i = 0; i != names.size(); ++i) {
        m_names.push_back(QString::fromStdString(names[i]));
    }
}


QVariant DeviceModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.row() < m_names.size()) {
            return m_names[index.row()];
        } else {
            qDebug() << "DeviceModel::data. Out of range: row =" << index.row();
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


int DeviceModel::rowCount(const QModelIndex&) const
{
    return m_names.size();
}


int DeviceModel::columnCount(const QModelIndex&) const
{
    return 1;
}


int DeviceModel::createContainer(const QString& name, StorageDescriptor& descriptor)
{
    AndroidDevice::Result result = m_device->createContainer(name.toStdString(), descriptor);

    if (result == AndroidDevice::CannotSave) {
        qDebug() << "Error creating container " << name << ": cannot save containers to file";
    }
    else if (result == AndroidDevice::CannotLoadImage) {
        qDebug() << "Error creating container " << name << ": cannot load image";
    }
    else if (result == AndroidDevice::IdAlreadyExists) {
        qDebug() << "Error creating container " << name << ": container with such id already exists";
    }
    else if (result == AndroidDevice::Alright) {
        m_names.push_back(name);
        emit(layoutChanged());
        emit(created(name)); //? m_device->getContainerInfo(name.toStdString())))
    } else {
        qDebug() << "Unknown error creating container " << name;
    }

    return 0;
}


int DeviceModel::destroyContainer(const QString& name)
{
    beginRemoveRows(QModelIndex(), getRow(name), getRow(name));

    AndroidDevice::Result result = m_device->destroyContainer(name.toStdString());

    if (result == -1) {
        qDebug() << "Error destroying container: not container with name " << name;
    }
    else if (result < 0) {
        qDebug() << "Unknown error destroying container " << name;
    }
    else if (result >= 0) {
        m_names.erase(std::find(m_names.begin(), m_names.end(), name));
        emit(layoutChanged());
    }

    endRemoveRows();

    return 0;
}


int DeviceModel::switchToContainer(const QString& name)
{
    return m_device->switchToContainer(name.toStdString());
}


int DeviceModel::startContainer(const QString& name)
{
    return m_device->startContainer(name.toStdString());
}


int DeviceModel::stopContainer(const QString& name)
{
    return m_device->stopContainer(name.toStdString());
}


ContainerInfo DeviceModel::getContainerInfo(const QString& name)
{
    return m_device->getContainerInfo(name.toStdString());
}


int DeviceModel::getRow(const QString& name) const
{
    for (int i = 0; i != m_names.size(); ++i) {
        if (name == m_names[i]) {
            return i;
        }
    }

    return -1;
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
