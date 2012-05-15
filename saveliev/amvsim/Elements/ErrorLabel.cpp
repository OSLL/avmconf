#include "ErrorLabel.h"

ErrorLabel::ErrorLabel(QWidget *parent) :
    QLabel(parent)
{
    setStyleSheet("ErrorLabel { color: red; }");
}
