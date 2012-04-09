#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H

#include <QAbstractItemModel>
#include "api/AndroidDevice.h"

class ContainerModel : public QAbstractItemModel {
    Q_OBJECT
private:
    AndroidDevice *device;
    std::string *name;

public:
    explicit ContainerModel(QObject *parent = 0);

signals:

public slots:

};

#endif // CONTAINERMODEL_H
