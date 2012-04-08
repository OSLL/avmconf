#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include <QItemDelegate>

class ContainerEditDelegate : public QItemDelegate {
    Q_OBJECT

public:
    explicit ContainerEditDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:


public slots:

};

#endif // CONTAINEREDITDELEGATE_H
