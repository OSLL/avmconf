#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel> 
#include <QSlider>
#include <sstream>

#include "ParametersWidget.h"


ParametersWidget::ParametersWidget(IDevice *device, const std::vector<Parameter*> &parameters, QWidget *parent)
    : QWidget(parent), m_device(device)
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(5, 5, 5, 5);
    layout()->setSpacing(10);
    
    initWidgetsForParameters(parameters);
}


void ParametersWidget::initWidgetsForParameters(const std::vector<Parameter*> &pars) 
{        
    typedef std::map<std::string, std::map<std::string, Parameter*> > ParamsByServicesMap;
    ParamsByServicesMap parsByServices;
    
    for (int pi = 0; pi != pars.size(); ++pi) {
        parsByServices[pars[pi]->getServiceName()][pars[pi]->getId()] = pars[pi];
    }
    
    for (ParamsByServicesMap::iterator si = parsByServices.begin(); si != parsByServices.end(); ++si) { 
        QWidget *parametersForAService = new QWidget;
        parametersForAService->setLayout(new QVBoxLayout);
        parametersForAService->layout()->setContentsMargins(0, 0, 0, 0);
        parametersForAService->layout()->setSpacing(0);
                 
        parametersForAService->layout()->addWidget(buildServiceLabel(new QLabel(QString::fromStdString(si->first))));     
        
        for (std::map<std::string, Parameter*>::iterator pi = si->second.begin(); pi != si->second.end(); ++pi) {
            QWidget *w = new QWidget();
            
            Parameter* par = pi->second;
            Parameter::Type type = par->getType();
            Value* value = m_device->getValue(par->getId());
            
            if (type == Parameter::Bool) { 
                buildBoolean(w, (BoolParameter*)par, ((BoolValue*)value)->getValue());
                
            } else if (type == Parameter::DoubleWithRange) {
                buildDoubleWithRange(w, (DoubleParameterWithRange*)par, ((DoubleValue*)value)->getValue()); 
                
            } else if (type == Parameter::Options) {
                buildOptions(w, (OptionsParameter*)par, ((OptionsValue*)value)->getValue());
            }   
            
            ((QVBoxLayout*)parametersForAService->layout())->addWidget(w, 0, Qt::AlignTop);   
        }            
        ((QVBoxLayout*)layout())->addWidget(parametersForAService, 0, Qt::AlignTop);   
    }   
}

QLabel *ParametersWidget::buildServiceLabel(QLabel *label)
{
    label->setStyleSheet("font-weight: bold");
    return label;
}

void ParametersWidget::buildBoolean(QWidget *w, BoolParameter *par, bool val)
{
    QCheckBox *chBox = new QCheckBox(par->getName().c_str());
    chBox->setChecked(val);
    
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    w->layout()->addWidget(chBox);
}

void ParametersWidget::buildDoubleWithRange(QWidget *w, DoubleParameterWithRange *par, double val)
{   
    w->setLayout(new QHBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    
    std::ostringstream strs;
    strs << val;
    
    w->layout()->addWidget(new QLabel(par->getName().c_str()));
    w->layout()->addWidget(new QLineEdit(QString::fromStdString(strs.str())));
}

void ParametersWidget::buildOptions(QWidget *w, OptionsParameter *par, int val)
{   
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);  
    w->layout()->setSpacing(0);
    
    QLabel *label = new QLabel(par->getName().c_str());
 //   label->setStyleSheet("margin-bottom: -4px");      
    
    w->layout()->addWidget(label);
    
    QRadioButton *rb;
    for (int i = 0; i != par->getOptions().size(); ++i) {
        rb = new QRadioButton(par->getOptions()[i].data());
        rb->setStyleSheet("margin-bottom: 5px");  
        w->layout()->addWidget(rb);
        if (i == val) {
            rb->setChecked(true);
        }            
    }
    rb->setStyleSheet("margin-bottom: 7px");    
}



