#include "container-info.h"
#include "api/StorageDescriptor.h"
#include <QString>

ContainerInfo::ContainerInfo(QString name, StorageDescriptor descr)
    : name(name), storageDescriptor(descr) {
}
