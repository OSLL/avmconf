#ifndef ICONTAINER_H
#define ICONTAINER_H

#include <string>

#include "ContainerState.h"
#include "StorageDescriptor.h"

class IContainer {
public:
    virtual ContainerState getState() const = 0;
    virtual const std::string& getName() const = 0;
    virtual const std::string& getImageAddress() const = 0;
    virtual int restoreImage(const std::string& imageAddress) = 0;
    virtual int loadImage(const StorageDescriptor& inpTemplate) = 0;
};

#endif // ICONTAINER_H
