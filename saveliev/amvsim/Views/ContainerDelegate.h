#ifndef CONTAINERDELEGATE_H
#define CONTAINERDELEGATE_H

#include <QStyledItemDelegate>

#include "../Models/ContainerListModel.h"

class ContainerDelegate : public QStyledItemDelegate {
    Q_OBJECT
private:
    ContainerListModel * m_model;

public:
    ContainerDelegate(QWidget *parent = 0);
 // virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index);
 // virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index);

 // void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

 // QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
 // void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

public slots:

};

#endif // CONTAINERDELEGATE_H
