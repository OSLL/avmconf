#ifndef NOSUCHCONTAINEREXCEPTION_H
#define NOSUCHCONTAINEREXCEPTION_H

#include <stdexcept>

class NoSuchContainerException : public std::exception
{
public:
    NoSuchContainerException(const std::string& msg) : m_msg(msg) { }

    virtual const char* what() const throw() {
        return m_msg.c_str();
    }

    virtual ~NoSuchContainerException() throw() {}

private:
    std::string m_msg;
};

#endif // NOSUCHCONTAINEREXCEPTION_H
