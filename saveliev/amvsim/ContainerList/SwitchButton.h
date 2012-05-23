#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QToolButton>
#include <QPushButton>

class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);
    
    void setStoppedContainerView();
    void setRunningInactiveContainerView();
    void setActiveContainerView();
    
signals:
    
public slots:
    
};

#endif // SWITCHBUTTON_H
