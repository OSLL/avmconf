#ifndef CONTAINERSLISTVIEW_H
#define CONTAINERSLISTVIEW_H

#include <QListView>
#include "container-widget.h"

class ContainersListView : public QListView {
    Q_OBJECT

public:
    explicit ContainersListView(QWidget *parent = 0);
    virtual void setModel(QAbstractItemModel * model);

signals:

private slots:
    void setItemWidget(QString);
 // void setWidget(const QModelIndex &parent, int start, int end);
 // virtual void rowsInserted(const QModelIndex &parent, int start, int end);
};

#endif // CONTAINERSLISTVIEW_H
