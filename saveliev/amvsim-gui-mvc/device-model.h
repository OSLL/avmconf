#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractTableModel>

#include "api.h"

class DeviceModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit DeviceModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
 // QModelIndex index(int row, int column, const QModelIndex &parent) const;
 // QModelIndex parent(const QModelIndex &child) const;

private:
    AndroidDevice m_device;

signals:

public slots:
    void createContainer();
};

#endif // DEVICEMODEL_H
