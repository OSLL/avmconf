#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <vector>
#include <QString>
#include <QAbstractTableModel>

#include "api/AndroidDevice.h"
#include "api/ContainerInfo.h"

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DeviceModel(AndroidDevice* device, QObject* parent = 0);

    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    int createContainer(const QString& name, StorageDescriptor& descriptor);
    int destroyContainer(const QString& name);
    int switchToContainer(const QString& name);
    int startContainer(const QString& name);
    int stopContainer(const QString& name);

    ContainerInfo getContainerInfo(const QString& name);

 // QModelIndex index(int row, int column, const QModelIndex&parent) const;
 // QModelIndex parent(const QModelIndex&child) const;

private:
    AndroidDevice* m_device;
    std::vector<QString> m_names;

    int getRow(const QString& name) const;

signals:
    void created(const QString&);
 // void rowsInserted ( const QModelIndex& parent, int start, int end );

public slots:

};

#endif // DEVICEMODEL_H
