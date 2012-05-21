
#include <QLabel>
#include <QHBoxLayout>
#include <sstream>

#include "DoubleParameterWithRangeWidget.h"

DoubleParameterWithRangeWidget::DoubleParameterWithRangeWidget(
        IDevice *device, DoubleParameterWithRange *par, double val, QWidget *parent)
    : ParameterWidget(device, par->getId(), parent)    
{
    setLayout(new QHBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);
    
    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setFixedWidth(200);
    m_slider->setRange(par->getMin(), par->getMax());
    m_slider->setValue(val);
    QObject::connect(m_slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
    
    std::ostringstream strs;
    strs << val;
    m_edit = new QLineEdit(QString::fromStdString(strs.str()));
    m_edit->setFixedWidth(50);
    QObject::connect(m_edit, SIGNAL(textChanged(QString)), this, SLOT(editChanged(QString)));
    
    layout()->addWidget(new QLabel(par->getName().c_str()));
    layout()->addWidget(m_edit);
    layout()->addWidget(m_slider);   
}

void DoubleParameterWithRangeWidget::editChanged(const QString &val)
{
    m_slider->setValue(val.toInt());
    emit(parameterChanged(m_parId, new DoubleValue(m_parId, val.toDouble())));
}

void DoubleParameterWithRangeWidget::sliderMoved(int newVal)
{
    std::ostringstream strs;
    strs << newVal;    
    m_edit->setText(QString::fromStdString(strs.str()));
    
    emit(parameterChanged(m_parId, new DoubleValue(m_parId, newVal)));
}
