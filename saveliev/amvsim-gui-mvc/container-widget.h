#ifndef CONTAINEREDITDELEGATE_H
#define CONTAINEREDITDELEGATE_H

#include "api/container-info.h"
#include <QItemDelegate>
#include <QPushButton>
#include <QLabel>

class ContainerWidget : public QWidget {
    Q_OBJECT

private:
    QPushButton *m_powerButton;
    QLabel *m_label;

public:
    explicit ContainerWidget(ContainerInfo info, QObject *parent = 0);

signals:


public slots:

};

#endif // CONTAINEREDITDELEGATE_H
