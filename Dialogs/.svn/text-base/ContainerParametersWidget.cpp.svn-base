#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>

#include "ContainerParametersWidget.h"

ContainerParametersWidget::ContainerParametersWidget(ContainerListModel *model, 
                                                     const QString &contName, QWidget *parent)
    : QWidget(parent), m_model(model)
{
    setLayout(new QVBoxLayout);
    setContentsMargins(0, 0, 0, 0);
    
    std::vector<Parameter*> parameters = m_model->getContainerParametersList();
    
    for (int pi = 0; pi != parameters.size(); ++pi) {
        if (parameters[pi]->getType() == Parameter::Bool) {
            QCheckBox *checkBox = new QCheckBox(((BoolParameter*)parameters[pi])->getName().data(), this);
            
            layout()->addWidget(checkBox);
        } 
        else if (parameters[pi]->getType() == Parameter::DoubleWithRange) {
            
        }
        else if (parameters[pi]->getType() == Parameter::Options) {
            OptionsParameter* par = (OptionsParameter*)parameters[pi];
            
            QWidget *options = new QWidget();
            options->setLayout(new QVBoxLayout);
            options->setContentsMargins(0, 0, 0, 0);
            for (int i = 0; i != par->getOptions().size(); ++i) {
                options->layout()->addWidget(new QRadioButton(par->getOptions()[i].data()));                
            }
            layout()->addWidget(options);
        }
    }
}
