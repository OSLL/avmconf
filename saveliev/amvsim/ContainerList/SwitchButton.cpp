#include "SwitchButton.h"

SwitchButton::SwitchButton(QWidget *parent) :
    QPushButton("Show", parent)
{    
    //setFixedSize(50, 30);
}

void SwitchButton::setStoppedContainerView()
{
    setEnabled(false);
    //setStyleSheet("background-color: #FFFFFF");
}

void SwitchButton::setActiveContainerView()
{
    setEnabled(false);
    //setStyleSheet("* { background-color: #0F65FA }");
}

void SwitchButton::setRunningInactiveContainerView()
{
    setEnabled(true);
    //setStyleSheet("background-color: #FFFFFF");
}

