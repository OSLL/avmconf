#include "ServiceInfo.h"

std::vector<std::string> ServiceInfo::getParametersIds() const 
{    
    std::vector<std::string> v;
    for(ParametersMap::const_iterator it = m_parameters.begin(); it != m_parameters.end(); ++it) {
        v.push_back(it->first);
    }
    return v;      
}

int ServiceInfo::getParametersCount() const
{
    return m_parameters.size();
}


Parameter *ServiceInfo::getParameter(const std::string &id) const 
{    
    return m_parameters.at(id);
}
