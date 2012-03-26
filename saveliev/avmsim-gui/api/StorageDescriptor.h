#ifndef STORAGEDESCRIPTOR_H
#define STORAGEDESCRIPTOR_H

// Class that represents any source of data

struct StorageDescriptor {
public:
    enum StorageDescriptorType {
        Http,
        Ftp,
        Local
    };

    StorageDescriptor(const std::string& address, StorageDescriptorType type) : m_address(address), m_type(type) { }

protected:
    std::string m_address;
    StorageDescriptorType m_type;
};

struct HttpURLStorageDescriptor: StorageDescriptor {
    HttpURLStorageDescriptor(const std::string& address) : StorageDescriptor(address, Http) { }
};
struct FtpURLStorageDescriptor: StorageDescriptor {
    FtpURLStorageDescriptor(const std::string& address) : StorageDescriptor(address, Ftp) { }
};
struct LocalFSStorageDescriptor: StorageDescriptor {
    LocalFSStorageDescriptor(const std::string& address) : StorageDescriptor(address, Local) { }
};

#endif // STORAGEDESCRIPTOR_H
