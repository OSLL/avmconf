#ifndef CONTAINERDELEGATE_H
#define CONTAINERDELEGATE_H

#include <QStyledItemDelegate>
#include "container-info.h"

class ContainerDelegate : public QStyledItemDelegate {
    Q_OBJECT
private:

public:
    ContainerDelegate(QWidget *parent);

   // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

public slots:

};

#endif // CONTAINERDELEGATE_H
