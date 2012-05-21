#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel> 
#include <QSlider>
#include <QDebug>
#include <sstream>

#include "ParametersWidget.h"
#include "ParameterWidgets.h"
#include <QButtonGroup>


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
    
    for (int pi = 0; pi != pars.size(); ++pi) {
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
            
            if (type == Parameter::Bool) { 
                w = buildBoolean((BoolParameter*)par, ((BoolValue*)value)->getValue());
                
            } else if (type == Parameter::DoubleWithRange) {
                w = buildDoubleWithRange((DoubleParameterWithRange*)par, ((DoubleValue*)value)->getValue()); 
                
            } else if (type == Parameter::Options) {
                w = buildOptions((OptionsParameter*)par, ((OptionsValue*)value)->getValue());
            }   
            
            if (w != 0) {
                ((QVBoxLayout*)parametersForAService->layout())->addWidget(w, 0, Qt::AlignTop); 
            }
        }       
        
        ((QVBoxLayout*)layout())->addWidget(parametersForAService, 0, Qt::AlignTop);   
    }   
}

QLabel *ParametersWidget::buildServiceLabel(QLabel *label)
{
    label->setStyleSheet("font-weight: bold");
    return label;
}

ParameterWidget *ParametersWidget::buildBoolean(BoolParameter *par, bool val)
{        
    BoolParameterWidget *w = new BoolParameterWidget(m_device, par->getId());   
    w->setLayout(new QVBoxLayout());
    
    QCheckBox *checkBox = new QCheckBox(par->getName().c_str());
    checkBox->setChecked(val);    
    QObject::connect(checkBox, SIGNAL(stateChanged(int)), w, SLOT(checkBoxChanged(int)));
    
    w->layout()->setContentsMargins(0, 0, 0, 0);
    w->layout()->addWidget(checkBox);
    
    return w;
}

ParameterWidget *ParametersWidget::buildDoubleWithRange(DoubleParameterWithRange *par, double val)
{   
    DoubleParameterWithRangeWidget *w = new DoubleParameterWithRangeWidget(m_device, par->getId()); 
    w->setLayout(new QHBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setFixedWidth(200);
    slider->setTickInterval(1);
    slider->setRange(par->getMin(), par->getMax());
    slider->setValue(val);
    QObject::connect(slider, SIGNAL(sliderMoved(int)), w, SLOT(sliderMoved(int)));
    
    std::ostringstream strs;
    strs << val;
    QLineEdit *edit = new QLineEdit(QString::fromStdString(strs.str()));
    edit->setFixedWidth(50);
    QObject::connect(edit, SIGNAL(textChanged(QString)), w, SLOT(editChanged(QString)));
    
    w->layout()->addWidget(new QLabel(par->getName().c_str()));
    w->layout()->addWidget(edit);
    w->layout()->addWidget(slider);
    
    return w;
}

ParameterWidget *ParametersWidget::buildOptions(OptionsParameter *par, int val)
{   
    OptionsParameterWidget *w = new OptionsParameterWidget(m_device, par->getId()); 
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);  
    w->layout()->setSpacing(0);
    
    QLabel *label = new QLabel(par->getName().c_str());  
    w->layout()->addWidget(label);
    
    QButtonGroup *radios = new QButtonGroup();    
    QObject::connect(radios, SIGNAL(buttonClicked(int)), w, SLOT(radioSwitched(int)));
    QRadioButton *rb;
    for (int i = 0; i != par->getOptions().size(); ++i) {
        rb = new QRadioButton(par->getOptions()[i].data());
        rb->setStyleSheet("margin-bottom: 5px");  
        radios->addButton(rb);
        w->layout()->addWidget(rb);
        if (i == val) {
            rb->setChecked(true);
        }
    }
    rb->setStyleSheet("margin-bottom: 7px");    
         
    return w;    
}



