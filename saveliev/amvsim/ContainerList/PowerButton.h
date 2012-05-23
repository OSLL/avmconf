#ifndef POWERBUTTON_H
#define POWERBUTTON_H

#include <QToolButton>
#include <QPushButton>

class PowerButton : public QToolButton
{
    Q_OBJECT
public:
    explicit PowerButton(QWidget *parent = 0);
    
    void setOn();
    void setOff();
    
signals:
    
public slots:
    
};

class TextPowerButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TextPowerButton(QWidget *parent = 0);
    
    void setOn();
    void setOff();
    
signals:
    
public slots:
    
};


#endif // POWERBUTTON_H
