#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractTableModel>
#include "api/AndroidDevice.h"
#include "api/ContainerInfo.h"

class DeviceModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit DeviceModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    int createContainer(QString name, StorageDescriptor descriptor);
    int destroyContainer(QString name);
    int switchToContainer(QString name);
    int startContainer(QString name);
    int stopContainer(QString name);
    ContainerInfo getContainerInfo(QString name);

 // QModelIndex index(int row, int column, const QModelIndex &parent) const;
 // QModelIndex parent(const QModelIndex &child) const;

private:
    AndroidDevice m_device;

signals:
    void created(QString);
 // void rowsInserted ( const QModelIndex & parent, int start, int end );

public slots:

};

#endif // DEVICEMODEL_H
