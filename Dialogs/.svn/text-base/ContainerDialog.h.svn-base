#ifndef CONTAINERDIALOG_H
#define CONTAINERDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "ContainerParametersWidget.h"
#include "../Models/ContainerListModel.h"

class ContainerDialog : public QDialog 
{
    Q_OBJECT

private:
    QPushButton *m_destroyButton;  
    ContainerParametersWidget *m_parameters;
    ContainerListModel *m_model;
    QString m_contName;
    
public:
    ContainerDialog(ContainerListModel *model, const QString &contName, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CONTAINERDIALOG_H
