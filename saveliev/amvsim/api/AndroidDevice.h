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
#include "Parameter.h"
#include "Service.h"

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
    const std::string& getActiveContainer() const;
    ContainerInfo getContainerInfo(const std::string& name) const;
    std::vector<std::string> getContainersIds() const;
    int getContainersNumber() const;
    
    void parameterChanged(int parameterId, Value newValue);      
    std::vector<Parameter*> getContainerParametersList() const;
    std::vector<Parameter*> getDeviceParametersList() const;     
    std::vector<Value*> getContainerParametersValues(const std::string& containerId) const;   
    std::vector<Value*> getDeviceParametersValues() const;    
    
//    ServiceInfo getServiceInfo(const std::string& id) const;
//    std::vector<std::string> getServicesIds() const;
//    int getServicesNumber() const;

private:
    typedef std::map<std::string, Container*> ContainersMap;
    ContainersMap m_containers;
    Container* m_activeContainer;

    typedef std::map<std::string, Service*> ServicesMap;
    ServicesMap m_services;

    Saver m_saver;
};

#endif // ANDROIDDEVICE_H








