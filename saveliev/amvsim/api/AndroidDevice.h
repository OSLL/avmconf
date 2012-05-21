#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include <string>
#include <map>
#include <vector>

#include "Container.h"
#include "ContainerInfo.h"
#include "StorageDescriptor.h"
#include "Saver.h"
#include "Parameter.h"
#include "Service.h"
#include "IDevice.h"

class AndroidDevice : public IDevice
{
public:
    AndroidDevice();
    virtual ~AndroidDevice();

    virtual Result createContainer(const std::string& containerName, const StorageDescriptor& inpTemplate);
    virtual Result destroyContainer(const std::string& containerName);
    virtual int startContainer(const std::string& containerName);
    virtual int stopContainer(const std::string& containerName);
    virtual int switchToContainer(const std::string& containerName);
    virtual int setContainerImage(const std::string& containerName, const StorageDescriptor& image);
    virtual int syncContainerImage(const std::string& containerName);
    virtual const std::string& getActiveContainer() const;
    virtual ContainerInfo getContainerInfo(const std::string& name) const;
    virtual std::vector<std::string> getContainersIds() const;
    virtual int getContainersNumber() const;
     
    virtual void parameterChanged(int parameterId, Value newValue);      
    virtual const std::vector<Parameter*> &getContainerParametersList() const;
    virtual const std::vector<Parameter*> &getDeviceParametersList() const;     
    virtual std::vector<Value*> getContainerParametersValues(const std::string& containerId) const;   
    virtual std::vector<Value*> getDeviceParametersValues() const;    
    
//    ServiceInfo getServiceInfo(const std::string& id) const;
//    std::vector<std::string> getServicesIds() const;
//    int getServicesNumber() const;

private:
    typedef std::map<std::string, Container*> ContainersMap;
    ContainersMap m_containers;
    Container* m_activeContainer;

    typedef std::map<std::string, Service*> ServicesMap;
    ServicesMap m_services;

    std::vector<Parameter*> m_deviceParameters;
    std::vector<Parameter*> m_containerParameters;
    
    Saver m_saver;
};

#endif // ANDROIDDEVICE_H








