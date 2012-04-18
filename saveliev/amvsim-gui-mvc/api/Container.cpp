#include "Container.h"

using std::string;

Container::Container(const string& containerName)
    : myName(containerName), myImageAddress(""), myState(StateStopped) {
}

int Container::loadImage(const StorageDescriptor& inpTemplate) {
    // Some iniitialization procedures with StorageDescriptor.
    myImageAddress = "address";

    return 0;
}

int Container::restoreImage(const std::string& imageAddress) {
    // initialization
    myImageAddress = imageAddress;

    return 0;
}

const ContainerState& Container::getState() const {
    return myState;
}

void Container::setState(const ContainerState& inpState) {
    myState = inpState;
}

const string& Container::getName() const {
    return myName;
}

Container::~Container(){
}

const string & Container::getImageAddress() const {
    return myImageAddress;
}
