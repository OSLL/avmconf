#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H

#include <QAbstractItemModel>

class ContainerModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit ContainerModel(QObject *parent = 0);

signals:

public slots:

};

#endif // CONTAINERMODEL_H
