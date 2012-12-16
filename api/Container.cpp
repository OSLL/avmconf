#include "Container.h"

using std::string;

Container::Container(const string& containerName)
    : m_name(containerName), m_imageAddress(""), m_state(Undefined) {
}

int Container::loadImage(const StorageDescriptor &) {
    // Some iniitialization procedures with StorageDescriptor.
    m_imageAddress = "address";

    return 0;
}

int Container::restoreImage(const std::string & imageAddress) {
    // initialization
    m_imageAddress = imageAddress;

    return 0;
}

const ContainerState& Container::getState() const {
    return m_state;
}

void Container::setState(const ContainerState& inpState) {
    m_state = inpState;
}

const string& Container::getName() const {
    return m_name;
}

Container::~Container(){
}

const string & Container::getImageAddress() const {
    return m_imageAddress;
}
