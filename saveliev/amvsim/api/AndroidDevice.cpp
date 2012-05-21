#include <iostream>

#include "NoSuchContainerException.h"
#include "AndroidDevice.h"
#include "Saver.h"

using std::string;
using std::map;
using std::pair;


AndroidDevice::AndroidDevice() : m_containers(), m_activeContainer(0), m_saver()
{
    m_saver.restore(m_containers);
    
    /////////////////
    // HARD CODED
    // // services
    Service* service = new Service("outgoingCalls");
    m_services.insert(std::make_pair("outgoingCalls", service));
    Service* service2 = new Service("incomingCalls");
    m_services.insert(std::make_pair("incomingCalls", service2));
        
    // // parameters
    std::vector<std::string> wifiOptions;
    wifiOptions.push_back("Point 1");
    wifiOptions.push_back("Point 2");
    wifiOptions.push_back("Point 3");
    m_deviceParameters.push_back(new OptionsParameter("wifi_access_points", "Access points", "WiFi", wifiOptions));    
    std::vector<std::string> wifiOptions2;
    wifiOptions2.push_back("Access pt");
    wifiOptions2.push_back("Alalala");
    wifiOptions2.push_back("Point of access");
    m_deviceParameters.push_back(new OptionsParameter("wifi_access_points2", "Access points 2", "WiFi", wifiOptions2));
        
    m_containerParameters.push_back(new BoolParameter("outgoing_calls_allowed", "Allowed", "Outgoing calls"));
    m_containerParameters.push_back(new BoolParameter("incoming_calls_allowed", "Allowed", "Incoming calls"));
    /////////////////
}


AndroidDevice::~AndroidDevice()
{
    for (map<string, Container*>::iterator it = this->m_containers.begin();
         it != this->m_containers.end(); ++it) {
        delete it->second;
    }
    
    for (std::vector<Parameter*>::iterator it = this->m_deviceParameters.begin();
         it != this->m_deviceParameters.end(); ++it) {
        delete *it;
    }
    
    for (std::vector<Parameter*>::iterator it = this->m_containerParameters.begin();
         it != this->m_containerParameters.end(); ++it) {
        delete *it;
    }
}


AndroidDevice::Result AndroidDevice::createContainer(const string & containerName, const StorageDescriptor & inpTemplate)
{
    Result result = UndefinedError;

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

    return result;
}


AndroidDevice::Result AndroidDevice::destroyContainer(const string & containerName)
{
    Result result = UndefinedError;

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

    return result;
}


int AndroidDevice::startContainer(const string & containerName)
{
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


int AndroidDevice::stopContainer(const string & containerName)
{
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


int AndroidDevice::switchToContainer(const string & containerName)
{
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


int AndroidDevice::setContainerImage(const string & containerName, const StorageDescriptor & image)
{
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


int AndroidDevice::syncContainerImage(const string &)
{
    int status = 0;
    // Do some stuff about sync.
    return status;
}


//std::vector<std::string> AndroidDevice::getContainersNames() const
//{
//    std::vector<int> names;
//    for(map<int,int>::iterator it = myContainers.begin(); it != myContainers.end(); ++it) {
//        names.push_back(it->first);
//        cout << it->first << "\n";
//    }
//    return names;
//}


const std::string & AndroidDevice::getActiveContainer() const
{
    return m_activeContainer->getName();
}


ContainerInfo AndroidDevice::getContainerInfo(const std::string &name) const
{
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


std::vector<std::string> AndroidDevice::getContainersIds() const
{
    std::vector<std::string> v;
    for(ContainersMap::const_iterator it = m_containers.begin(); it != m_containers.end(); ++it) {
        v.push_back(it->first);
    }
    return v;
}


int AndroidDevice::getContainersNumber() const
{
    return m_containers.size();
}


//ServiceInfo AndroidDevice::getServiceInfo(const std::string &id) const
//{    
//    Service* service = (Service*)(m_services.at(id));
    
//    /////////////
//    // HARD CODED
//    ServiceInfo s(id, "OutGoingCalls");
//    s.m_parameters.insert(std::make_pair(id, new BoolParameter("Allowed", "Allowed", true)));
//    s.m_parameters.insert(std::make_pair(id, new BoolParameter("Allowed2", "Allowed", true)));
//    return s;
//    /////////////
//}


//std::vector<std::string> AndroidDevice::getServicesIds() const
//{
//    std::vector<std::string> v;
//    for(ServicesMap::const_iterator it = m_services.begin(); it != m_services.end(); ++it) {
//        v.push_back(it->first);
//    }
//    return v;    
//}


//int AndroidDevice::getServicesNumber() const
//{
//    return m_services.size();
//}


void AndroidDevice::parameterChanged(int parameterId, Value *newValue)
{
    delete newValue;
}

Value *AndroidDevice::getValue(const std::string &parameterId) const
{
    if (parameterId == "outgoing_calls_allowed") return new BoolValue(parameterId, true);
    if (parameterId == "incoming_calls_allowed") return new BoolValue(parameterId, false);
    if (parameterId == "wifi_access_points")     return new OptionsValue(parameterId, 1);
}

const std::vector<Parameter*> &AndroidDevice::getContainerParametersList() const
{     
    return m_containerParameters;
}

const std::vector<Parameter*> &AndroidDevice::getDeviceParametersList() const
{
    return m_deviceParameters;    
}









