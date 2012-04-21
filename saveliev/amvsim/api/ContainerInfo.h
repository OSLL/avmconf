#ifndef CONTAINERINFO_H
#define CONTAINERINFO_H

#include <QMetaType>
#include "StorageDescriptor.h"
#include "ContainerState.h"

struct ContainerInfo {
    ContainerInfo() : name(""), address("") {}
    ContainerInfo(const std::string& name, const std::string& address, const ContainerState& state)
        : name(name), address(address), state(state) {}

    QString toString() {
        return QString::fromStdString(name);
    }

    std::string name;
    std::string address;
    ContainerState state;
};
Q_DECLARE_METATYPE(ContainerInfo)

#endif // CONTAINERINFO_H
