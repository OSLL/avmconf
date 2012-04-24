#include <iostream>

#include "NoSuchContainerException.h"
#include "AndroidDevice.h"
#include "Saver.h"

using std::string;
using std::map;
using std::pair;

AndroidDevice::AndroidDevice() : m_containers(), m_activeContainer(0), m_saver() {
    m_saver.restore(m_containers);
}

AndroidDevice::~AndroidDevice() {
    for (map<string, Container*>::iterator it = this->m_containers.begin(); it != this->m_containers.end(); ++it) {
        delete it->second;
    }
}

// -1: container with such name already exists
// -2: cannot load image
// -3: cannot open file to save
int AndroidDevice::createContainer(const string & containerName, const StorageDescriptor & inpTemplate) {
    int status = 0;
    Container * container;
    if (m_containers.find(containerName) == this->m_containers.end()) {
        container = new Container(containerName);

        if (container->loadImage(inpTemplate) != 0) {
            status = -2;
        }
        m_containers.insert(pair<string, Container*>(containerName, container));

        if (m_saver.save(m_containers) != 0) {
            status = -3;
        }
    } else {
        status = -1;
    }

    return status;
}

int AndroidDevice::startContainer(const string & containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()){
        containerIter->second->setState(StateRunning); //Do same stuff about starting container.
        /* added by Vlad Saveliev */ if (m_activeContainer == 0) switchToContainer(containerName);
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::stopContainer(const string & containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()){
        containerIter->second->setState(StateStopped); //Do same stuff about stopping container.
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::destroyContainer(const string & containerName) {
    int status = 0;
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()){
        if (this->m_activeContainer == containerIter->second){
            this->m_activeContainer = NULL;
        }
        delete containerIter->second;
        this->m_containers.erase(containerIter);
        m_saver.save(m_containers);
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::switchToContainer(const string & containerName){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()){
        this->m_activeContainer = containerIter->second;
        status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::setContainerImage(const string & containerName, const StorageDescriptor & image){
    int status = 0;
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()) {
        if (((Container*)containerIter->second)->loadImage(image) != 0)
            status = -2;
        else
            status = 0;
    } else {
        status = -1;
    }
    return status;
}

int AndroidDevice::syncContainerImage(const string &){
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
    return m_containers.size();
}

//const std::string& AndroidDevice::getContainerNameAt(int n) const
//{
//    int k = 0;
//    for(map<std::string, Container*>::const_iterator it = m_containers.begin(); it != m_containers.end(); ++it) {
//        if (k == n) {
//            return it->first;
//        }
//        ++k;
//    }
//    throw std::out_of_range("");
//}

//ContainerInfo AndroidDevice::getContainerInfoAt(int n) const
//{
//    return getContainerInfo(getContainerNameAt(n));
//}

ContainerInfo AndroidDevice::getContainerInfo(const std::string &name) const
{
    std::cout << name << std::endl;
    if (m_containers.find(name) != m_containers.end()) {
        Container* cont = (Container*)(m_containers.at(name));
     // if (cont != 0) {
        ContainerInfo info;
        info.name = name;
        info.state = cont->getState();
        return info;
    } else {
        throw NoSuchContainerException(name);
    }
}

std::vector<std::string> AndroidDevice::getContainersNames() const
{
    std::vector<std::string> v;
    for(ContainersMap::const_iterator it = m_containers.begin(); it != m_containers.end(); ++it) {
        v.push_back(it->first);
    }
    return v;
}

const std::string & AndroidDevice::getActiveContainer() const
{
    return m_activeContainer->getName();
}







