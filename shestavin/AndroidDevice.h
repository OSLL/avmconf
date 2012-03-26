#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include <string>
#include <map>
#include "StorageDescriptor.h"
#include "Container.h"

using std::string;
using std::map;
using std::pair;

struct AndroidDevice {

    virtual int createContainer(const string&  containerName, const StorageDescriptor& inpTemplate);

    virtual int startContainer(const string&  containerName);

    virtual int stopContainer(const string&  containerName);

    virtual int destroyContainer(const string&  containerName);

    virtual int switchToContainer(const string&  containerName);

    virtual int setContainerImage(const string&  containerName, const StorageDescriptor&  image);

    virtual int syncContainerImage(const string&  containerName);

    AndroidDevice();

    virtual ~AndroidDevice();

private:

    map<string, Container*> myContainers;

    Container* activeContainer;

    friend class Tests;


};

#endif // ANDROIDDEVICE_H
