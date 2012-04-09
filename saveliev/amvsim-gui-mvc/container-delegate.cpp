#include "container-delegate.h"

ContainerDelegate::ContainerDelegate(QWidget *parent = 0)
    : QStyledItemDelegate(parent) {

}

QSize ContainerDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(300, 70);
}

void ContainerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

}
