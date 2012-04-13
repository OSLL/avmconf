#include "containers-list-view.h"
#include "container-widget.h"
#include <iostream>

ContainersListView::ContainersListView(QWidget *parent) :
    QListView(parent) {
}

//void ContainersListView::setWidget(const QModelIndex &parent, int start, int end) {
//    std::cout << "rowsInserted" << std::endl;
//    for (int i = start; i != end; ++i) {
//        setIndexWidget(parent.child(i, 0), new ContainerWidget);
//        std::cout << "rowInserted" << std::endl;
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
    connect(model, SIGNAL(created(QString)), this, SLOT(setItemWidget(QString)));
 // connect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), m_view, SLOT(setWidget(QModelIndex, int, int)));
}
