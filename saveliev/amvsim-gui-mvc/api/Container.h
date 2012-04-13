#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include "StorageDescriptor.h"
//#include "ContainerInfo.h"
#include "ContainerState.h"

using std::string;

struct Container {

    virtual const ContainerState& getState() const; //Maybe should chang to isStarted() and isStopped()?

    virtual void setState(const ContainerState& inpState); //Maybe should chang to setStarted() and setStopped()?

    virtual const string& getName() const;

 // virtual ContainerInfo getInfo() const;

    Container(const string& containerName, const StorageDescriptor& inpTemplate);
    virtual ~Container();

private:

    ContainerState myState;
    const string& myName;
    StorageDescriptor myDescriptor;

    virtual void init(const StorageDescriptor& inpTemplate);

};

#endif // CONTAINER_H
