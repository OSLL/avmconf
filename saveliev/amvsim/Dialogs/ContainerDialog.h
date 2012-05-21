#ifndef CONTAINERDIALOG_H
#define CONTAINERDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "ParameterWidgets/ParametersWidget.h"
#include "ContainerList/ContainerListModel.h"

class ContainerDialog : public QDialog 
{
    Q_OBJECT

private:
    QPushButton *m_doneButton;    
    QPushButton *m_destroyButton;
    QPushButton *m_cancelDestroyButton;
    
    ParametersWidget *m_parameters;
    ContainerListModel *m_model;
    QString m_contName;
    
    QWidget *initButtons();
    QWidget *initParameters();
    
    bool m_toDestroy;
    
public:
    ContainerDialog(ContainerListModel *model, const QString &contName, QWidget *parent = 0);
    
signals:
    
public slots:
    void destroyPressed();
    void cancelDestroyPressed();
    
};

#endif // CONTAINERDIALOG_H
