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
    const std::string& getName() { return m_name; }
    const std::string& getId() { return m_id; }
    
protected:
    Parameter(const std::string &id, const std::string& name)
        : m_id(id), m_name(name) { }
        
    std::string m_id;
    std::string m_name;    
};


class DoubleWithRangeParameter : public Parameter {
public:
    virtual Type getType() { return DoubleWithRange; }
    
    DoubleWithRangeParameter(const std::string &id, const std::string& name, double min, double max, double value)
        : Parameter(id, name), m_min(min), m_max(max), m_value(value) { }
    
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }
    double getValue() const { return m_value; }
        
private:
    double m_min;
    double m_max;
    double m_value;
};

class OptionsParameter : public Parameter {
public:    
    virtual Type getType() { return Options; }
    
    OptionsParameter(const std::string &id, const std::string& name, int value)
        : Parameter(id, name), m_value(value) { }
    
    void setOption(int value, const std::string& option) { m_options[value] = option; }
    std::map<int, std::string> &getOptions() { return m_options; }
    int getValue() const { return m_value; }
    
private:
    std::map<int, std::string> m_options;
    int m_value;
};

class BoolParameter : public Parameter {
public:
    virtual Type getType() { return Bool; }
    
    BoolParameter(const std::string& id, const std::string& name, bool value)
        : Parameter(id, name), m_value(value) { }
    
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









