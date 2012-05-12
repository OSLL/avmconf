#include <QVBoxLayout>
#include <QLabel>

#include "ServiceListView.h"
#include "ServiceView.h"

ServiceListView::ServiceListView(QWidget *parent) :
    QListView(parent)
{
    setAutoFillBackground(true);
}


void ServiceListView::setModel(ServiceListModel *model)
{
    QListView::setModel(model);
    setWidgets(0, model->rowCount());
}


void ServiceListView::rowsInserted(const QModelIndex &, int start, int end)
{
    setWidgets(start, end+1);
}

    
void ServiceListView::setWidgets(int start, int end) 
{
    for (int i = start; i != end; ++i) {
        QVariant data = model()->data(model()->index(i, 0), Qt::DisplayRole).toString();
        
        ServiceView *view = new ServiceView((ServiceListModel*)model(), this);
        ServiceModel *serviceModel = new ServiceModel(data.toString(), (ServiceListModel*)model(), model());
        view->setModel(serviceModel);
    
    // QWidget *widget = new QWidget(this);
    // widget->setAutoFillBackground(true);
    // widget->setLayout(new QVBoxLayout);
    // widget->layout()->addWidget(new QLabel(model()->headerData(0, Qt::Vertical, Qt::DisplayRole).toString()));        
    // widget->layout()->addWidget(view);
        
        setIndexWidget(model()->index(i, 0), view);
    } 
}

