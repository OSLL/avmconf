#include "Container.h"

Container::Container(const string&  containerName, const StorageDescriptor& inpTemplate):myName(containerName){
    this->myState = StateStopped;    //Maybe should use as parameter?
    this->init(inpTemplate);
}


void Container::init(const StorageDescriptor& inpTemplate){
    //Some iniitialization procedures with StorageDescriptor.
    FILE *in;
    char buff[512];
    string command = "lxc-create -f /lxc/" + this->myName + ".conf " +  "-n " + this->myName;
    string type = "r";
    in = popen(command.c_str(), type.c_str());  // ???
    if (!in){
        //Write to log message "Can't execute command: " + command
    }
    string result = "";
    while (fgets(buff, sizeof(buff), in) != NULL){
        result += buff;
    }
    if (result != "'" + this->myName + "' created"){
        this->myState = StateError;
        //Write to log message "Error in container creation: " + result
    }
    pclose(in);
}

const Container::ContainerState& Container::getState() const{
    return this->myState;
}

void Container::setState(const ContainerState& inpState){
    this->myState = inpState;
}

const string& Container::getName() const{
    return this->myName;
}

Container::~Container(){

}
