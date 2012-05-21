#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <map>
#include <vector>
#include <string>


class Parameter {
public:
    enum Type {
        DoubleWithRange,
        Options,
        Bool
    };
       
    virtual Type getType() = 0;
    const std::string& getId() { return m_id; }
    const std::string& getName() { return m_name; }
    const std::string& getServiceName() { return m_serviceName; }
    
protected:
    Parameter(const std::string &id, const std::string& name, const std::string& serviceName)
        : m_id(id), m_name(name), m_serviceName(serviceName) { }
        
    std::string m_id;
    std::string m_name;    
    std::string m_serviceName;
};

class DoubleParameterWithRange : public Parameter {
public:
    virtual Type getType() { return DoubleWithRange; }
    
    DoubleParameterWithRange(const std::string& id, const std::string& name, 
                             const std::string& serviceName, double min, double max)
        : Parameter(id, name, serviceName), m_min(min), m_max(max) { }
    
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }
        
private:
    double m_min;
    double m_max;
};

class OptionsParameter : public Parameter {
public:    
    virtual Type getType() { return Options; }
    
    OptionsParameter(const std::string &id, const std::string& name, 
                     const std::string& serviceName, std::vector<std::string> options)
        : Parameter(id, name, serviceName), m_options(options) { }
    
 // void setOption(int value, const std::string& option) { m_options[value] = option; }
    std::vector<std::string> getOptions() const { return m_options; }
    
private:
    std::vector<std::string> m_options;
};

class BoolParameter : public Parameter {
public:
    virtual Type getType() { return Bool; }
    
    BoolParameter(const std::string& id, const std::string& name, const std::string& serviceName)
        : Parameter(id, name, serviceName) { }
};




class Value {
public:
    const std::string& getParameterId() { return m_parameterId; }
    
protected:
    Value(const std::string &parameterId) : m_parameterId(parameterId) { 
    }
    
    std::string m_parameterId;
};

class DoubleValue : public Value {
public:
    DoubleValue(const std::string &parameterId, double value) : Value(parameterId), m_value(value){ 
    }
    
    double getValue() const { return m_value; }
  
private:
    double m_value;
};

class OptionsValue : public Value {
public:
    OptionsValue(const std::string &parameterId, int value) : Value(parameterId), m_value(value){ 
    }
    
    bool getValue() const { return m_value; }
  
private:
    int m_value;
};

class BoolValue : public Value {
public:
    BoolValue(const std::string &parameterId, bool value) : Value(parameterId), m_value(value){ 
    }
    
    bool getValue() const { return m_value; }
  
private:
    bool m_value;
};











class ServiceInfo {
    friend class AndroidDevice;
    
public:
    typedef std::map<std::string, Parameter*> ParametersMap;
    
    ServiceInfo() { } 
    ServiceInfo(const std::string& id, const std::string& name) : m_id(id), m_name(name) { }
    
    const std::string& getName() const { return m_name; }
    const std::string& getId() const { return m_id; }
    std::vector<std::string> getParametersIds() const;
    int getParametersCount() const;
    Parameter *getParameter(const std::string &id) const;
    
private:
    std::string m_id;
    std::string m_name;
    ParametersMap m_parameters;
};

#endif // SERVICEINFO_H









