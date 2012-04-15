#include "AndroidDevice.h"

AndroidDevice::AndroidDevice():myContainers(){
    this->activeContainer = NULL;
}

AndroidDevice::~AndroidDevice(){
    for (map<string, Container*>::iterator it = this->myContainers.begin(); it != this->myContainers.end(); ++it){
        delete it->second;
    }
}

int AndroidDevice::createContainer(const string&  containerName, const StorageDescriptor& inpTemplate){
    int status = 0;
    if (this->myContainers.find(containerName) == this->myContainers.end()){
        this->myContainers.insert(pair<string, Container*>(containerName, new Container(containerName, inpTemplate)));
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::startContainer(const string&  containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        containerIter->second->setState(Container::StateRunning); //Do same stuff about starting container.
        status = 0;
    } else {
        status = -1;
    }
    return status;
}


int AndroidDevice::stopContainer(const string&  containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->myContainers.find(containerName);
    if (containerIter != this->myContainers.end()){
        containerIter->second->setState(Container::StateStopped); //Do same stuff about stopping container.
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::destroyContainer(const string&  containerName){
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

int AndroidDevice::switchToContainer(const string&  containerName){
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

int AndroidDevice::setContainerImage(const string&  containerName, const StorageDescriptor& image){
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

int AndroidDevice::syncContainerImage(const string&  containerName){
    int status = 0;
    // Do some stuff about sync.
    return status;
}
