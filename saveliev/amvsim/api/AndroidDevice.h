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
#include "Service.h"
#include "ServiceInfo.h"


class AndroidDevice
{
public:
    AndroidDevice();
    virtual ~AndroidDevice();

    enum Result {
        UndefinedError,
        Alright,
        IdAlreadyExists,
        NoSuchId,
        CannotLoadImage,
        CannotSave
    };
    virtual Result createContainer(const std::string& containerName, const StorageDescriptor& inpTemplate);
    virtual Result destroyContainer(const std::string& containerName);
    virtual int startContainer(const std::string& containerName);
    virtual int stopContainer(const std::string& containerName);
    virtual int switchToContainer(const std::string& containerName);
    virtual int setContainerImage(const std::string& containerName, const StorageDescriptor& image);
    virtual int syncContainerImage(const std::string& containerName);
    int getContainersNumber() const;
    const std::string& getActiveContainer() const;
    ContainerInfo getContainerInfo(const std::string& name) const;
    std::vector<std::string> getContainersNames() const;
    
    void parameterChanged(int serviceId, int parameterId, double newValue) const;  
    void parameterChanged(int serviceId, int parameterId, const std::string& newValue) const;
    void parameterChanged(int serviceId, int parameterId, bool newValue) const;
    std::vector<ServiceInfo> & getServicesInfo() const;
       

private:
    typedef std::map<std::string, Container*> ContainersMap;
    ContainersMap m_containers;
    Container* m_activeContainer;

    std::vector<Service> m_services;

    Saver m_saver;
};

#endif // ANDROIDDEVICE_H








