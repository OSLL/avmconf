#ifndef IDEVICE_H
#define IDEVICE_H

#include <string>
#include <vector>
#include "StorageDescriptor.h"
#include "ContainerInfo.h"
#include "Parameter.h"

class IDevice
{    
public:    
    enum Result {
        UndefinedError,
        Alright,
        IdAlreadyExists,
        NoSuchId,
        CannotLoadImage,
        CannotSave
    };

    virtual Result createContainer(const std::string& containerName, const StorageDescriptor& inpTemplate) = 0;
    virtual Result destroyContainer(const std::string& containerName) = 0;
    virtual int startContainer(const std::string& containerName) = 0;
    virtual int stopContainer(const std::string& containerName) = 0;
    virtual int switchToContainer(const std::string& containerName) = 0;
    virtual int setContainerImage(const std::string& containerName, const StorageDescriptor& image) = 0;
    virtual int syncContainerImage(const std::string& containerName) = 0;
    
    virtual const std::string& getActiveContainer() const = 0;
    virtual ContainerInfo getContainerInfo(const std::string& name) const = 0;
    virtual std::vector<std::string> getContainersIds() const = 0;
    virtual int getContainersNumber() const = 0;
     
    virtual const std::vector<Parameter*> &getContainerParametersList() const = 0;
    virtual const std::vector<Parameter*> &getDeviceParametersList() const = 0;
    virtual void parameterChanged(int parameterId, Value *newValue) = 0;
    virtual Value *getValue(const std::string& parameterId) const = 0;
};

#endif // IDEVICE_H
