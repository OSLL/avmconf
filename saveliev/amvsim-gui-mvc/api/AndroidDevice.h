#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include <string>
#include <map>
#include "Container.h"
#include "ContainerInfo.h"
#include "StorageDescriptor.h"

struct AndroidDevice {

    virtual int createContainer(const std::string&  containerName, const StorageDescriptor& inpTemplate);

    virtual int startContainer(const std::string&  containerName);

    virtual int stopContainer(const std::string&  containerName);

    virtual int destroyContainer(const std::string&  containerName);

    virtual int switchToContainer(const std::string&  containerName);

    virtual int setContainerImage(const std::string&  containerName, const StorageDescriptor&  image);

    virtual int syncContainerImage(const std::string&  containerName);

    // added by Vlad Saveliev

    virtual int getContainersNumber() const;

    virtual ContainerInfo getContainerInfoAt(int n) const;

    virtual const std::string& getContainerNameAt(int n) const;

    virtual ContainerInfo getContainerInfo(const std::string& name) const;

    virtual const std::string& getActiveContainer() const;

    AndroidDevice();

    virtual ~AndroidDevice();

private:

    std::map<std::string, Container*> myContainers;

    Container* activeContainer;

};

#endif // ANDROIDDEVICE_H
