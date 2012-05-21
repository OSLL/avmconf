#ifndef STORAGEDESCRIPTOR_H
#define STORAGEDESCRIPTOR_H

#include <string>

// Class that represents any source of data
struct StorageDescriptor {
public:
    enum StorageDescriptorType {
        Http,
        Ftp,
        Local
    };

    StorageDescriptor() { }
    StorageDescriptor(const std::string& address) : address(address) { }
    StorageDescriptor(const std::string& address, StorageDescriptorType type) : address(address), type(type) { }

    std::string address;
    StorageDescriptorType type;
};

#endif // STORAGEDESCRIPTOR_H
