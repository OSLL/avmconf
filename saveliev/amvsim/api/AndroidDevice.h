#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include "Container.h"
#include "ContainerInfo.h"
#include "StorageDescriptor.h"
#include "Saver.h"

struct AndroidDevice
{
    AndroidDevice();
    virtual ~AndroidDevice();

    virtual int createContainer(const std::string& containerName, const StorageDescriptor& inpTemplate);
    virtual int startContainer(const std::string& containerName);
    virtual int stopContainer(const std::string& containerName);
    virtual int destroyContainer(const std::string& containerName);
    virtual int switchToContainer(const std::string& containerName);
    virtual int setContainerImage(const std::string& containerName, const StorageDescriptor& image);
    virtual int syncContainerImage(const std::string& containerName);
    int getContainersNumber() const;
    const std::string& getActiveContainer() const;
    ContainerInfo getContainerInfo(const std::string& name) const;
    std::vector<std::string> getContainersNames() const;

private:
    typedef std::map<std::string, Container*> ContainersMap;
    ContainersMap m_containers;
    Container* m_activeContainer;
    Saver m_saver;
};

#endif // ANDROIDDEVICE_H







