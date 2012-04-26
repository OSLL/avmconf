#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include "StorageDescriptor.h"
#include "ContainerState.h"

class Container {
public:
    virtual const ContainerState& getState() const; //Maybe should change to isStarted() and isStopped()?
    virtual void setState(const ContainerState& inpState); //Maybe should change to start() and stop()?
    virtual const std::string& getName() const;
    virtual const std::string& getImageAddress() const;
    virtual int restoreImage(const std::string& imageAddress);
    virtual int loadImage(const StorageDescriptor& inpTemplate);
    
    Container(const std::string& containerName);
    virtual ~Container();

private:
    std::string m_name;
    std::string m_imageAddress;
    ContainerState m_state;
};

#endif // CONTAINER_H

