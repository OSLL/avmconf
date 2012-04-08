#include "container-edit-delegate.h"
#include <QLineEdit>

ContainerEditDelegate::ContainerEditDelegate(QObject *parent) : QItemDelegate(parent) {
}

QWidget * ContainerEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    QLineEdit *editor = new QLineEdit(parent);

    return editor;
}

void ContainerEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    QString name = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    edit->setText(name);
}

void ContainerEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

    QLineEdit *edit = static_cast<QLineEdit*>(editor);
  //  edit->interpretText();
    QString name = edit->text();

    model->setData(index, name, Qt::EditRole);
}

void ContainerEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    editor->setGeometry(option.rect);
}
