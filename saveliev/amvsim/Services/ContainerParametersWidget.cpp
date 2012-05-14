#include "ContainerParametersWidget.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>

ContainerParametersWidget::ContainerParametersWidget(const AndroidDevice* device, QWidget *parent) :
    m_device(device), QWidget(parent)
{    
    setLayout(new QVBoxLayout);
    
    setContentsMargins(0, 0, 0, 0);
    
    std::vector<Parameter> parameters = m_device->getContainerParametersList();
    
    for (int pi = 0; pi != parameters.size(); ++pi) {
        if (parameters[pi].getType() == Parameter.Bool) {
            layout()->addChildWidget(new QCheckBox(((BoolParameter)parameters[pi]).getName()));
        } 
        else if (parameters[pi].getType() == Parameter.DoubleWithRange) {
            
        }
        else if (parameters[pi].getType() == Parameter.Options) {
            OptionsParameter par = parameters[pi];
            
            QWidget *options = new QWidget();
            options->setLayout(new QVBoxLayout);
            options->setContentsMargins(0, 0, 0, 0);
            for (int i = 0; i != par.getOptions(); ++i) {
                options->layout()->addChildWidget(new QRadioButton(par.getOptions()[i]));                
            }
            layout()->addChildWidget(options);
        }
    }
}
