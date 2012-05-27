#ifndef ICONTAINER_H
#define ICONTAINER_H

#include <string>

#include "ContainerState.h"
#include "StorageDescriptor.h"

class IContainer {
public:
    virtual const ContainerState getState() const = 0; //Maybe should change to isStarted() and isStopped()?
    virtual void setState(const ContainerState inpState) = 0; //Maybe should change to start() and stop()?
    virtual const std::string& getName() const = 0;
    virtual const std::string& getImageAddress() const = 0;
    virtual int restoreImage(const std::string& imageAddress) = 0;
    virtual int loadImage(const StorageDescriptor& inpTemplate) = 0;
};

#endif // ICONTAINER_H
