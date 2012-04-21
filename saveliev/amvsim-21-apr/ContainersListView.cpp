
#include <QDebug>

#include "ContainerDelegate.h"
#include "ContainersListView.h"
#include "ContainerWidget.h"

ContainersListView::ContainersListView(QWidget *parent) :
    QListView(parent) {
    setItemDelegate(new ContainerDelegate(this));
}

//void ContainersListView::setWidget(const QModelIndex & parent, int start, int end) {
//    qDebug() << "rowsInserted";
//    for (int i = start; i != end; ++i) {
//        setIndexWidget(parent.child(i, 0), new ContainerWidget);
//        qDebug() << "rowsInserted";
//    }
//}

void ContainersListView::setItemWidget(QString name) {
    if (model() != 0) {
        for (int row = 0; row != model()->rowCount(); ++row) {
            if (indexWidget(model()->index(row, 0)) == 0) {
                setIndexWidget(model()->index(row, 0), new ContainerWidget(name, (DeviceModel*)model(), this));
            }
        }
    }
}

void ContainersListView::setModel(QAbstractItemModel *model) {
    QListView::setModel(model);

    DeviceModel * dModel = (DeviceModel*)model;
    for (int i = 0; i != dModel->rowCount(); ++i) {
        QString name = dModel->data(dModel->index(i, 0), Qt::DisplayRole).toString();
        setIndexWidget(dModel->index(i, 0), new ContainerWidget(name, dModel, this));
    }

    connect(model, SIGNAL(created(QString)), this, SLOT(setItemWidget(QString)));
 // connect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), m_view, SLOT(setWidget(QModelIndex, int, int)));
}


