#ifndef CONTAINERINFO_H
#define CONTAINERINFO_H

#include <Qstring>
#include "api/StorageDescriptor.h"

struct ContainerInfo {
    ContainerInfo(QString name, StorageDescriptor descr);

    QString name;
    StorageDescriptor storageDescriptor;
};

#endif // CONTAINERINFO_H
