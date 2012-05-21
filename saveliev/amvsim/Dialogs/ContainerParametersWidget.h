#ifndef CONTAINERPARAMETERSWIDGET_H
#define CONTAINERPARAMETERSWIDGET_H

#include <QWidget>

#include "../Models/ContainerListModel.h"

class ContainerParametersWidget : public QWidget
{
    Q_OBJECT
private:
    ContainerListModel *m_model;
    
    void initWidgetsForParameters();
    
    static void buildBoolean        (QWidget *w, BoolParameter *par);
    static void buildDoubleWithRange(QWidget *w, DoubleParameterWithRange *par);
    static void buildOptions        (QWidget *w, OptionsParameter *par);
    
public:
    ContainerParametersWidget(ContainerListModel* model, const QString &contName, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CONTAINERPARAMETERSWIDGET_H
