#include <QDebug>

#include "ContainerDelegate.h"
#include "ContainerListView.h"
#include "ContainerWidget.h"
#include "../Dialogs/ContainerDialog.h"

ContainerListView::ContainerListView(QWidget *parent)
    : QListView(parent)
{
    
}


void ContainerListView::setModel(QAbstractItemModel *model)
{
    QListView::setModel(model);
    setWidgets(0, model->rowCount()); 
}


void ContainerListView::rowsInserted(const QModelIndex &, int start, int end)
{
    setWidgets(start, end+1);
}


void ContainerListView::itemPressed(const QString &contName)
{
    ContainerDialog *contDialog = new ContainerDialog((ContainerListModel*)model(), contName);
    contDialog->show();
}


void ContainerListView::setWidgets(int start, int end) 
{
    for (int i = start; i != end; ++i) {
        QVariant data = model()->data(model()->index(i, 0), Qt::DisplayRole).toString();
        ContainerWidget *widget = new ContainerWidget(data, model(), this, &m_containerWidgets);
        setIndexWidget(model()->index(i, 0), widget);
        
        connect(widget, SIGNAL(pressed(const QString&)), this, SLOT(itemPressed(const QString&)));
    }       
}

