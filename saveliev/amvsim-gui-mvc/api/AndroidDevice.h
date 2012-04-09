#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include <string>
#include <map>
#include "StorageDescriptor.h"
#include "Container.h"

struct AndroidDevice {

    virtual int createContainer(const std::string&  containerName, const StorageDescriptor& inpTemplate);

    virtual int startContainer(const std::string&  containerName);

    virtual int stopContainer(const std::string&  containerName);

    virtual int destroyContainer(const std::string&  containerName);

    virtual int switchToContainer(const std::string&  containerName);

    virtual int setContainerImage(const std::string&  containerName, const StorageDescriptor&  image);

    virtual int syncContainerImage(const std::string&  containerName);

    virtual int getContainersNumber() const;

    virtual const std::string& getContainerNameAt(int i) const;

    AndroidDevice();

    virtual ~AndroidDevice();

private:

    std::map<std::string, Container*> myContainers;

    Container* activeContainer;

    friend class Tests;


};

#endif // ANDROIDDEVICE_H
