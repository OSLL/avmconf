#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include "StorageDescriptor.h"
#include "ContainerState.h"

struct Container {

    virtual const ContainerState& getState() const; //Maybe should chang to isStarted() and isStopped()?

    virtual void setState(const ContainerState& inpState); //Maybe should chang to setStarted() and setStopped()?

    virtual const std::string& getName() const;

    virtual const std::string& getImageAddress() const;

    virtual int restoreImage(const std::string& imageAddress);

    virtual int loadImage(const StorageDescriptor& inpTemplate);

    Container(const std::string& containerName);
    virtual ~Container();

private:
    std::string myName;
    std::string myImageAddress;
    ContainerState myState;
};

#endif // CONTAINER_H
