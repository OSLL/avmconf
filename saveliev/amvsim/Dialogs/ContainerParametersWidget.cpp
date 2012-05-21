#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>

#include "ContainerParametersWidget.h"
#include <QLineEdit>
#include <QLabel>

ContainerParametersWidget::ContainerParametersWidget(ContainerListModel *model, 
                                                     const QString &contName, QWidget *parent)
    : QWidget(parent), m_model(model)
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(5, 5, 5, 5);
    layout()->setSpacing(10);
    
    initWidgetsForParameters();
}

void ContainerParametersWidget::initWidgetsForParameters() {
    const std::vector<Parameter*> &pars = m_model->getContainerParametersList();
    
    typedef std::map<std::string, std::map<std::string, Parameter*> > ParsBySersMap;
    ParsBySersMap parsByServices;
    
    for (int pi = 0; pi != pars.size(); ++pi) {
        parsByServices[pars[pi]->getServiceName()][pars[pi]->getId()] = pars[pi];    
    }    
    
    for (ParsBySersMap::iterator si = parsByServices.begin(); si != parsByServices.end(); ++si) { 
        QWidget *parametersForAService = new QWidget;
        parametersForAService->setLayout(new QVBoxLayout);
        parametersForAService->layout()->setContentsMargins(0, 0, 0, 0);
        parametersForAService->layout()->setSpacing(0);
        
        parametersForAService->layout()->addWidget(new QLabel(QString::fromStdString(si->first)));     
        
        for (std::map<std::string, Parameter*>::iterator pi = si->second.begin(); pi != si->second.end(); ++pi) {
            QWidget *w = new QWidget();
            
            Parameter* par = pi->second;
            Parameter::Type type = par->getType();
            
            if (type == Parameter::Bool) { 
                buildBoolean(w, (BoolParameter*)par);
                
            } else if (type == Parameter::DoubleWithRange) {
                buildDoubleWithRange(w, (DoubleParameterWithRange*)par); 
                
            } else if (type == Parameter::Options) {
                buildOptions(w, (OptionsParameter*)par);
            }   
            
            ((QVBoxLayout*)parametersForAService->layout())->addWidget(w, 0, Qt::AlignTop);
        }            
        ((QVBoxLayout*)layout())->addWidget(parametersForAService, 0, Qt::AlignTop);    
    }   
}

void ContainerParametersWidget::buildBoolean(QWidget *w, BoolParameter *par)
{
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    
    w->layout()->addWidget(new QCheckBox(par->getName().c_str()));
}

void ContainerParametersWidget::buildDoubleWithRange(QWidget *w, DoubleParameterWithRange *par)
{   
    w->setLayout(new QHBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    
    w->layout()->addWidget(new QLabel(par->getName().c_str()));
    w->layout()->addWidget(new QLineEdit);
}

void ContainerParametersWidget::buildOptions(QWidget *w, OptionsParameter *par)
{   
    w->setLayout(new QVBoxLayout);
    w->layout()->setContentsMargins(0, 0, 0, 0);
    
    for (int i = 0; i != par->getOptions().size(); ++i) {
        w->layout()->addWidget(new QRadioButton(par->getOptions()[i].data()));                
    }
}
