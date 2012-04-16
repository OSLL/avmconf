#include <stdexcept>
#include <exception>
#include <iostream>

#include "AndroidDevice.h"
#include "Saver.h"

using std::string;
using std::map;
using std::pair;

AndroidDevice::AndroidDevice() : myContainers(), activeContainer(0), mySaver() {
    mySaver.restore(myContainers);
}

AndroidDevice::~AndroidDevice(){
    for (map<string, Container*>::iterator it = this->myContainers.begin(); it != this->myContainers.end(); ++it) {
        delete it->second;
    }
}

// -1: container with such name already exists
// -2: cannot load image
// -3: cannot open file to save
int AndroidDevice::createContainer(const string& containerName, const StorageDescriptor& inpTemplate) {
    int status = 0;
    Container * container;
    if (myContainers.find(containerName) == this->myContainers.end()) {
        container = new Container(containerName);

        if (container->loadImage(inpTemplate) != 0) {
            status = -2;
        }
        myContainers.insert(pair<string, Container*>(containerName, container));

        if (mySaver.save(myContainers) != 0) {
            status = -3;
        }
    } else {
        status = -1;
    }

    return status;
}

int AndroidDevice::startContainer(const string& containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        containerIter->second->setState(StateRunning); //Do same stuff about starting container.
        /* added by Vlad Saveliev */ if (activeContainer == 0) switchToContainer(containerName);
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::stopContainer(const string& containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        containerIter->second->setState(StateStopped); //Do same stuff about stopping container.
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::destroyContainer(const string& containerName) {
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        if (this->activeContainer == containerIter->second){
            this->activeContainer = NULL;
        }
        delete containerIter->second;
        this->myContainers.erase(containerIter);
        mySaver.save(myContainers);
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::switchToContainer(const string& containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        this->activeContainer = containerIter->second;
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::setContainerImage(const string& containerName, const StorageDescriptor& image){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()) {
        if (((Container*)containerIter->second)->loadImage(image) != 0)
            status = -2;
        else
            status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::syncContainerImage(const string& containerName){
    int status = 0;
    // Do some stuff about sync.
    return status;
}

//std::vector<std::string> AndroidDevice::getContainersNames() const {
//    std::vector<int> names;
//    for(map<int,int>::iterator it = myContainers.begin(); it != myContainers.end(); ++it) {
//        names.push_back(it->first);
//        cout << it->first << "\n";
//    }
//    return names;
//}

int AndroidDevice::getContainersNumber() const {
    return myContainers.size();
}

const std::string& AndroidDevice::getContainerNameAt(int n) const {
    int k = 0;
    for(map<std::string, Container*>::const_iterator it = myContainers.begin(); it != myContainers.end(); ++it) {
        if (k == n) {
            return it->first;
        }
        ++k;
    }
    throw std::out_of_range("");
}

ContainerInfo AndroidDevice::getContainerInfoAt(int n) const {
    return getContainerInfo(getContainerNameAt(n));
}

ContainerInfo AndroidDevice::getContainerInfo(const std::string &name) const {
    std::cout << name << std::endl;
    if (myContainers.find(name) != myContainers.end()) {
        Container* cont = (Container*)(myContainers.at(name));
     //   if (cont != 0) {
        ContainerInfo info;
        info.name = name;
        info.state = cont->getState();
        return info;
    } else {
        throw NoSuchContainer(name);
    }
}

const std::string & AndroidDevice::getActiveContainer() const {
    return activeContainer->getName();
}







