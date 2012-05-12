#include <QHBoxLayout>
#include <QCheckBox>

#include "ServiceModel.h"
#include "ServiceView.h"

ServiceView::ServiceView(ServiceListModel* serviceListModel, QWidget * parent)
    : QListView(parent), m_serviceListModel(serviceListModel)
{  
    setAutoFillBackground(true);
}


void ServiceView::setModel(QAbstractItemModel *model)
{
    QListView::setModel(model);
    setWidgets(0, model->rowCount()); 
}


void ServiceView::rowsInserted(const QModelIndex&, int start, int end)
{  
    setWidgets(start, end+1);
}


void ServiceView::setWidgets(int start, int end) 
{
    for (int i = start; i != end; ++i) {
        QVariant data = model()->data(model()->index(i, 0), Qt::DisplayRole).toString();
        
        Parameter *param = ((ServiceModel*)model())->getParameter(data);
        
        QWidget *paramWidget = 0;
        if (param->getType() == Parameter::Bool) {
            paramWidget = new QCheckBox(QString::fromStdString(param->getName()), this);
            
            BoolParameter *boolParam = (BoolParameter*)param;
            QCheckBox *checkBox = (QCheckBox*)paramWidget;
            
            checkBox->setChecked(boolParam->getValue());
        } else if (param->getType() == Parameter::DoubleWithRange) {
            
        } else if (param->getType() == Parameter::Options) {
            
        } else {
            
        }
        
        paramWidget->setAutoFillBackground(true);
        setIndexWidget(model()->index(i, 0), paramWidget);
    }       
}






