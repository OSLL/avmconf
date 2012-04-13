#ifndef CONTAINERINFO_H
#define CONTAINERINFO_H

#include "StorageDescriptor.h"
#include "ContainerState.h"

struct ContainerInfo {
    ContainerInfo(const std::string& name, const StorageDescriptor& descriptor, const ContainerState& state)
        : name(name), storageDescriptor(descriptor), state(state) {}

    std::string name;
    StorageDescriptor storageDescriptor;
    ContainerState state;
};

#endif // CONTAINERINFO_H
