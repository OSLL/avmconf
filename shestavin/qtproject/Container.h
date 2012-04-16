#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <stdio.h>
#include "StorageDescriptor.h"

using std::string;

struct Container {

    enum ContainerState { StateRunning, StateStopped, StateError };

    virtual const ContainerState&  getState() const; //Maybe should chang to isStarted() and isStopped()?

    virtual void  setState(const ContainerState& inpState); //Maybe should chang to setStarted() and setStopped()?

    virtual const string& getName() const;

    Container(const string&  containerName, const StorageDescriptor& inpTemplate);
    virtual ~Container();

private:

    ContainerState myState;
    const string& myName;

    virtual void init(const StorageDescriptor& inpTemplate);

};

#endif // CONTAINER_H
