
#include <QPushButton>
#include <QPainter>
#include <QStylePainter>

#include "ContainerDelegate.h"
#include "ContainerWidget.h"

ContainerDelegate::ContainerDelegate(QWidget * parent) : QStyledItemDelegate(parent) { }

//void ContainerDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
//    QPushButton * widget = new QPushButton("Button name", (QWidget*)parent()); // new ContainerWidget(index, m_model, parent);

//    QPixmap pixmap(widget->size());
//    widget->render(&pixmap);

//    // QStylePainter stylePainter(painter->device());
//    // stylePainter.drawControl(QStyle::CE_PushButton, option);
//}


//QSize ContainerDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
//    return QSize(300, 70);
//}

//void ContainerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

//}

//QWidget *ContainerDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) {
//    return new ContainerWidget(this);
//}

//void ContainerDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
// // QString name = index.model()->data(index, Qt::EditRole).toString();

// // QLineEdit *edit = static_cast<QLineEdit*>(editor);
// // edit->setText(name);
//}

//void ContainerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
// //  QLineEdit *edit = static_cast<QLineEdit*>(editor);
// //  edit->interpretText();
// // QString name = edit->text();

// // model->setData(index, name, Qt::EditRole);
//}

//void ContainerDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) {
//    editor->setGeometry(option.rect);
//}
