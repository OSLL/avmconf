#include "Container.h"

Container::Container(const string& containerName, const StorageDescriptor& inpTemplate):myName(containerName) {
    this->myState = StateStopped;    //Maybe should use as parameter?
    this->init(inpTemplate);
}

void Container::init(const StorageDescriptor& inpTemplate) {
    //Some iniitialization procedures with StorageDescriptor.
}

const Container::ContainerState& Container::getState() const {
    return this->myState;
}

void Container::setState(const ContainerState& inpState) {
    this->myState = inpState;
}

const string& Container::getName() const {
    return this->myName;
}

Container::~Container() {

}
