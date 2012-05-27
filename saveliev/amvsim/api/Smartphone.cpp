/* -*- c-basic-offset: 4 -*- */

#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>

#include "Smartphone.h"

#define LXCPATH "/usr/local/var/lib/lxc"

// ================================================================================

using std::string;
using std::map;
using std::pair;

// ================================================================================

static int spawn_and_wait(const char* args[]) {
    int status = fork();
    if (status == 0) {
        exit(execvp(args[0], (char* const*)args));
    } else if (status > 0) {
        waitpid(status, &status, 0);

        status = (WEXITSTATUS(status) == 0) ? 0 : -1;
    }

    return status;
}

// --------------------------------------------------------------------------------

SmartphoneContainer::SmartphoneContainer(const string& containerName)
    : m_name(containerName), m_state(StateStopped) { }

SmartphoneContainer::~SmartphoneContainer() { }                                          

int SmartphoneContainer::loadImage(const StorageDescriptor& sd) {
    return 0;
}

int SmartphoneContainer::restoreImage(const std::string& imageAddress) {
    return 0;
}

ContainerState SmartphoneContainer::getState() const {
    return m_state;
}

const string& SmartphoneContainer::getName() const {
    return m_name;
}

const string& SmartphoneContainer::getImageAddress() const {
    return nothing;
}

int SmartphoneContainer::start() {
    const char* v[] = { "lxc-start", "-n", m_name.c_str(), "-d", NULL };
    int res = spawn_and_wait(v);

    if (res == 0) {
        m_state = StateRunning;
    }

    return res;
}

ContainerInfo SmartphoneContainer::info() const {
    return ContainerInfo(m_name, "", m_state);
}

int SmartphoneContainer::switchTo() {
    const char* v[] = { "switch_fg", m_name.c_str(), NULL };

    return spawn_and_wait(v);
}

// --------------------------------------------------------------------------------

Smartphone::Smartphone()
{
    DIR* cdir = opendir(LXCPATH);
    if (cdir) {
        struct dirent* d;
        struct stat s;

        while ((d = readdir(cdir))) {
            char cpath[NAME_MAX];

            snprintf(cpath, sizeof(cpath), "%s/%s/config", LXCPATH, d->d_name);
            if (stat(cpath, &s) == 0) {
                m_containers.insert(std::make_pair(d->d_name, new SmartphoneContainer(d->d_name)));
            }
        }
    }
}


Smartphone::~Smartphone()
{
    for (ContainerMap::iterator it = m_containers.begin(); it != m_containers.end(); ++it) {
        delete it->second;
    }
}

SmartphoneContainer* Smartphone::getContainer(const std::string& name) {
    ContainerMap::iterator cit = m_containers.find(name);
    if (cit != m_containers.end()) {
        return cit->second;
    } else {
        throw NoSuchContainerException(name);
    }    
}

const SmartphoneContainer* Smartphone::getContainer(const std::string& name) const {
    ContainerMap::const_iterator cit = m_containers.find(name);
    if (cit != m_containers.end()) {
        return cit->second;
    } else {
        throw NoSuchContainerException(name);
    }    
}

IDevice::Result Smartphone::createContainer(const string& containerName, const StorageDescriptor& inpTemplate)
{
        
    Result result = UndefinedError;

    /*
    Container * container;
    if (m_containers.find(containerName) != this->m_containers.end()) {
        result = IdAlreadyExists;
    } else {
        container = new Container(containerName);

        if (container->loadImage(inpTemplate) != 0) {
            result = CannotLoadImage;
        } else {
            m_containers.insert(pair<string, Container*>(containerName, container));

            if (m_saver.save(m_containers) != 0) {
                result = CannotSave;
            } else {
                result = Alright;
            }
        }
    }
    */

    return result;
}


Smartphone::Result Smartphone::destroyContainer(const string & containerName)
{
    Result result = UndefinedError;

    /*
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);

    if (containerIter == this->m_containers.end()) {
        result = NoSuchId;
    } else {
        if (this->m_activeContainer == containerIter->second) {
            this->m_activeContainer = 0;
        }
        delete containerIter->second;
        this->m_containers.erase(containerIter);

        if (m_saver.save(m_containers) != 0) {
            result = CannotSave;
        } else {
            result = Alright;
        }
    }
    */

    return result;
}


int Smartphone::startContainer(const string& containerName)
{
    return getContainer(containerName)->start();
    
    // map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    // if (containerIter != this->m_containers.end()){
    //     containerIter->second->setState(StateRunning); //Do same stuff about starting container.
    //     /* added by Vlad Saveliev */ if (m_activeContainer == 0) switchToContainer(containerName);
    //     status = 0;
    // } else {
    //     status = -1;
    // }

}


int Smartphone::stopContainer(const string & containerName)
{
    int status = 0;

    /*
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()){
        containerIter->second->setState(StateStopped); //Do same stuff about stopping container.
        status = 0;
    } else {
        status = -1;
    }
    */

    return status;
}


int Smartphone::switchToContainer(const string& containerName)
{
    SmartphoneContainer* c = getContainer(containerName);

    int status = c->switchTo();

    if (status == 0) {
        m_activeContainer = c;
    }

    /*
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()){
        this->m_activeContainer = containerIter->second;
        status = 0;
    } else {
        status = -1;
    }
    */

    return status;
}


int Smartphone::setContainerImage(const string & containerName, const StorageDescriptor & image)
{
    int status = 0;

    /*
    map<string, Container*>::iterator containerIter = this->m_containers.find(containerName);
    if (containerIter != this->m_containers.end()) {
        if (((Container*)containerIter->second)->loadImage(image) != 0)
            status = -2;
        else
            status = 0;
    } else {
        status = -1;
    }
    */

    return status;
}


int Smartphone::syncContainerImage(const string &)
{
    int status = 0;
    // Do some stuff about sync.
    return status;
}


//std::vector<std::string> Smartphone::getContainersNames() const
//{
//    std::vector<int> names;
//    for(map<int,int>::iterator it = myContainers.begin(); it != myContainers.end(); ++it) {
//        names.push_back(it->first);
//        cout << it->first << "\n";
//    }
//    return names;
//}


const std::string& Smartphone::getActiveContainer() const
{
    return m_activeContainer->getName();
}


ContainerInfo Smartphone::getContainerInfo(const std::string& name) const
{
    return getContainer(name)->info();

    /*
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
    */


    //return ContainerInfo();
}


std::vector<std::string> Smartphone::getContainersIds() const
{
    std::vector<std::string> v;

    for(ContainerMap::const_iterator it = m_containers.begin(); it != m_containers.end(); ++it) {
        v.push_back(it->first);
    }

    return v;
}


int Smartphone::getContainersNumber() const
{
    return m_containers.size();
}

void Smartphone::parameterChanged(int parameterId, Value *newValue)
{
}


const std::vector<Parameter*> &Smartphone::getContainerParametersList(const std::string &contName) const
{ 
    return m_containerParameters;
}

const std::vector<Parameter*> &Smartphone::getDeviceParametersList() const
{
    return m_parameters;    
}

Value *Smartphone::getValue(const std::string& parameterId) const {
    return NULL;
}
