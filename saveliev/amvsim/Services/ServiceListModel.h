#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <vector>
#include <QString>
#include <QAbstractListModel>

#include "../api/AndroidDevice.h"
#include "../api/ServiceInfo.h"

class ServiceListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ServiceListModel(AndroidDevice* device, QObject* parent = 0);

    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    ServiceInfo getServiceInfo(const QString &) const;

private:
    AndroidDevice* m_device;
    std::vector<QString> m_serviceIds;

    int getRow(const QString&) const;
};

#endif // DEVICEMODEL_H
