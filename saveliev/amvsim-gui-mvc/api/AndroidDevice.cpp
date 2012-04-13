#include <stdexcept>
#include <exception>
#include <iostream>
#include "AndroidDevice.h"

using std::string;
using std::map;
using std::pair;

class NoSuchContainer : std::exception {
    std::string msg;

public:
    NoSuchContainer(const std::string& msg) : msg(msg) { }

    virtual const char* what() const throw() {
        return msg.c_str();
    }

    virtual ~NoSuchContainer() throw() {}
};

AndroidDevice::AndroidDevice() : myContainers(), activeContainer(0) {
}

AndroidDevice::~AndroidDevice(){
    for (map<string, Container*>::iterator it = this->myContainers.begin(); it != this->myContainers.end(); ++it){
        delete it->second;
    }
}

int AndroidDevice::createContainer(const string& containerName, const StorageDescriptor& inpTemplate){
    int status = 0;
    if (this->myContainers.find(containerName) == this->myContainers.end()){
        this->myContainers.insert(pair<string, Container*>(containerName, new Container(containerName, inpTemplate)));
        status = 0;
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

int AndroidDevice::destroyContainer(const string& containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        if (this->activeContainer == containerIter->second){
            this->activeContainer = NULL;
        }
        delete containerIter->second;
        this->myContainers.erase(containerIter);
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
    if (containerIter != this->myContainers.end()){
        delete containerIter->second;
        containerIter->second = new Container(containerName, image);
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







