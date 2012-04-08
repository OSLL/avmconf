#ifndef CONTAINERDELEGATE_H
#define CONTAINERDELEGATE_H

#include <QStyledItemDelegate>

class ContainerDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit ContainerDelegate(QWidget *parent = 0);

signals:

public slots:

};

#endif // CONTAINERDELEGATE_H
