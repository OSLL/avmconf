#ifndef DEVICEPARAMETERSDIALOG_H
#define DEVICEPARAMETERSDIALOG_H

#include <QDialog>
#include <Views/ParametersWidget.h>

class DeviceParametersDialog : public QDialog
{
    Q_OBJECT
    
private:
    QPushButton *m_doneButton;   
    ParametersWidget *m_parameters;
    IDevice *m_device;
    
    QWidget *initButtons();
    QWidget *initParameters();
    
public:
    explicit DeviceParametersDialog(IDevice *device, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // DEVICEPARAMETERSDIALOG_H
