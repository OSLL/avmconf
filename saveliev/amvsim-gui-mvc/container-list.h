#ifndef CONTAINERLIST_H
#define CONTAINERLIST_H

#include <QWidget>

class ContainerList : public QWidget
{
    Q_OBJECT

    QListView   *m_view;
    QPushButton  m_createButton;

public:
    explicit ContainerList(QWidget *parent = 0);

signals:

public slots:

};

#endif // CONTAINERLIST_H
