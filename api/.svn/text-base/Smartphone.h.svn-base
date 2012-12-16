/* -*- mode: c++; c-basic-offset: 4 -*- */

#include "IDevice.h"
#include "IContainer.h"
#include "NoSuchContainerException.h"

// ================================================================================

class SmartphoneContainer : public IContainer {
public:
    SmartphoneContainer(const std::string& containerName);
    ~SmartphoneContainer();

    ContainerState getState() const;
    const std::string& getName() const;
    const std::string& getImageAddress() const;
    int restoreImage(const std::string& imageAddress);
    int loadImage(const StorageDescriptor& inpTemplate);


    int start();
    int switchTo();
    ContainerInfo info() const;
    
private:
    std::string m_name;
    std::string m_imageAddress;
    ContainerState m_state;

    std::string nothing;
};

// --------------------------------------------------------------------------------

class Smartphone : public IDevice {
public:
    Smartphone();
    ~Smartphone();


    Result createContainer(const std::string& containerName, const StorageDescriptor& inpTemplate);
    Result destroyContainer(const std::string& containerName);
    int startContainer(const std::string& containerName);
    int stopContainer(const std::string& containerName);
    int switchToContainer(const std::string& containerName);
    int setContainerImage(const std::string& containerName, const StorageDescriptor& image);
    int syncContainerImage(const std::string& containerName);
    const std::string& getActiveContainer() const;
    ContainerInfo getContainerInfo(const std::string& name) const;
    std::vector<std::string> getContainersIds() const;
    int getContainersNumber() const;

    void parameterChanged(int parameterId, Value newValue);      
    std::vector<Parameter*> getContainerParametersList() const;
    std::vector<Parameter*> getDeviceParametersList() const;     
    std::vector<Value*> getContainerParametersValues(const std::string& containerId) const;   
    std::vector<Value*> getDeviceParametersValues() const;    

private:
    typedef std::map<std::string, SmartphoneContainer*> ContainerMap;

    ContainerMap m_containers;
    IContainer* m_activeContainer;

    const SmartphoneContainer* getContainer(const std::string& name) const;
    SmartphoneContainer* getContainer(const std::string& name);
};
