
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QDebug>
#include <sstream>
#include <QButtonGroup>

#include "ParametersWidget.h"
#include "ListParameterWidget.h"

ParametersWidget::ParametersWidget(IDevice *device, const std::vector<Parameter*> &parameters, QWidget *parent)
    : QWidget(parent), m_device(device)
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(15, 15, 15, 15);
    layout()->setSpacing(10);
    
    initWidgetsForParameters(parameters);
}

void ParametersWidget::initWidgetsForParameters(const std::vector<Parameter*> &pars) 
{        
    typedef std::map<std::string, std::map<std::string, Parameter*> > ParamsByServicesMap;
    ParamsByServicesMap parsByServices;
    
    for (unsigned pi = 0; pi != pars.size(); ++pi) {
        parsByServices[pars[pi]->getServiceName()][pars[pi]->getId()] = pars[pi];
    }
    
    for (ParamsByServicesMap::iterator si = parsByServices.begin(); si != parsByServices.end(); ++si) { 
        QWidget *parametersForAService = new QWidget;
        parametersForAService->setLayout(new QVBoxLayout);
        parametersForAService->layout()->setContentsMargins(0, 0, 0, 0);
        parametersForAService->layout()->setSpacing(0);
                 
        parametersForAService->layout()->addWidget(buildServiceLabel(new QLabel(QString::fromStdString(si->first))));     
        
        Value *value;
        Parameter *par;
        for (std::map<std::string, Parameter*>::iterator pi = si->second.begin(); pi != si->second.end(); ++pi) {
            ParameterWidget *w = 0;
            
            par = pi->second;
            Parameter::Type type = par->getType();
            value = m_device->getValue(par->getId());
            
            if (value != 0) {                
                if (type == Parameter::Bool) { 
                    w = new BoolParameterWidget(m_device, 
                           (BoolParameter*)par, ((BoolValue*)value)->getValue());
                    
                } else if (type == Parameter::DoubleWithRange) {
                    w = new DoubleParameterWithRangeWidget(m_device, 
                            (DoubleParameterWithRange*)par, ((DoubleValue*)value)->getValue());
                    
                } else if (type == Parameter::Options) {
                    OptionsParameter *optPar = (OptionsParameter*)par;
//                  if (optPar->getOptions().size() < 5) {
                        w = new OptionsParameterWidget(m_device, 
                               (OptionsParameter*)optPar, ((OptionsValue*)value)->getValue());
//                  } 
//                    else {
//                        w = new ListParameterWidget(m_device, 
//                               (OptionsParameter*)optPar, ((OptionsValue*)value)->getValue());
//                    }
                }
                
                if (w != 0) {
                    ((QVBoxLayout*)parametersForAService->layout())->addWidget(w, 0, Qt::AlignTop); 
                }
            }
        }       
        
        if (si->second.begin() != si->second.end()) {
            ((QVBoxLayout*)layout())->addWidget(parametersForAService, 0, Qt::AlignTop);   
        }
    }
}

QLabel *ParametersWidget::buildServiceLabel(QLabel *label)
{
    label->setStyleSheet("font-weight: bold");
    return label;
}


