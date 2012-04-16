#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include "StorageDescriptor.h"
#include "ContainerState.h"

using std::string;

struct Container {

    virtual const ContainerState& getState() const; //Maybe should chang to isStarted() and isStopped()?

    virtual void setState(const ContainerState& inpState); //Maybe should chang to setStarted() and setStopped()?

    virtual const string& getName() const;

    virtual const string& getImageAddress() const;

    virtual int restoreImage(const std::string& imageAddress);

    virtual int loadImage(const StorageDescriptor& inpTemplate);

    Container(const string& containerName);
    virtual ~Container();

private:
    ContainerState myState;
    string myName;
    string myImageAddress;
};

#endif // CONTAINER_H
