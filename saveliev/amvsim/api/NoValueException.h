#ifndef NOVALUEEXCEPTION_H
#define NOVALUEEXCEPTION_H

#include <stdexcept>

class NoValueException : public std::exception
{
public:
    NoValueException(const std::string& msg) : m_msg(msg) { }  
    
    virtual const char* what() const throw() {
        return m_msg.c_str();
    }

    virtual ~NoValueException() throw() {}

private:
    std::string m_msg;
};

#endif // NOVALUEEXCEPTION_H
