#ifndef SERVICE_H
#define SERVICE_H

#include <map>
#include <vector>
#include <string>

struct ServiceInfo {
    ServiceInfo(std::string id, const std::string& name) : id(id), name(name) { }

    std::string id;
    std::string name;
    std::vector<Parameter> parameters;
};


class Parameter {
public:
    enum Type {
        DoubleWithRange,
        Options,
        Bool
    };
    
    virtual Type getType() = 0;
    
protected:
    Parameter(std::string id, const std::string& name)
        : m_id(id), m_name(name) { }
        
    std::string m_id;
    std::string m_name;    
};


class DoubleWithRangeParameter : public Parameter {
public:
    virtual Type getType() { return DoubleWithRange; }
    
    DoubleWithRange(std::string id, const std::string& name, double min, double max, double value)
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
    
    OptionsParameter(std::string id, const std::string& name, int value)
        : Parameter(id, name), m_value(value) { }
    
    void setOption(int value, const std::string& option) { m_options[value] = option; }
    std::map<int, std::string>& getOptions() const { return m_options; }
    int getValue() const { return m_value; }
    
private:
    std::map<int, std::string> m_options;
    int m_value;
};

class BoolParameter : public Parameter {
public:
    virtual Type getType() { return Bool; }
    
    BoolParameter(std::string id, const std::string& name, bool value)
        : Parameter(id, name), m_value(value) { }
    
    bool getValue() const { return m_value; }
    
private:
    bool m_value;
};

#endif // SERVICE_H









