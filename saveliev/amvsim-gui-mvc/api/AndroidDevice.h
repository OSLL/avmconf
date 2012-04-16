#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include <string>
#include <map>
#include <fstream>

#include "Container.h"
#include "ContainerInfo.h"
#include "StorageDescriptor.h"
#include "Saver.h"

class NoSuchContainer : std::exception {
    std::string msg;

public:
    NoSuchContainer(const std::string& msg) : msg(msg) { }

    virtual const char* what() const throw() {
        return msg.c_str();
    }

    virtual ~NoSuchContainer() throw() {}
};

struct AndroidDevice {

    virtual int createContainer(const std::string&  containerName, const StorageDescriptor& inpTemplate);

    virtual int startContainer(const std::string&  containerName);

    virtual int stopContainer(const std::string&  containerName);

    virtual int destroyContainer(const std::string&  containerName);

    virtual int switchToContainer(const std::string&  containerName);

    virtual int setContainerImage(const std::string&  containerName, const StorageDescriptor&  image);

    virtual int syncContainerImage(const std::string&  containerName);


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

    Saver mySaver;

};

#endif // ANDROIDDEVICE_H








