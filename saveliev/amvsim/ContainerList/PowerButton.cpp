#include "PowerButton.h"

PowerButton::PowerButton(QWidget *parent) :
    QToolButton(parent)
{
    setIconSize(QSize(30, 30));
    setFixedSize(30, 30);    
}

void PowerButton::setOn()
{
    setIcon(QIcon("/Users/vladsaveliev/Dropbox/AU/practice/avmconf/saveliev/amvsim/Images/button-enabled.png"));    
}

void PowerButton::setOff()
{
    setIcon(QIcon("/Users/vladsaveliev/Dropbox/AU/practice/avmconf/saveliev/amvsim/Images/button-disabled.png"));   
}

TextPowerButton::TextPowerButton(QWidget *parent) :
    QPushButton(parent)
{  
    setFixedWidth(70);
}

void TextPowerButton::setOn()
{
     setText("Stop");
}

void TextPowerButton::setOff()
{
    setText("Run");
}


