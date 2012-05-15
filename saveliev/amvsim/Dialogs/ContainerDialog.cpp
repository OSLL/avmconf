#include "ContainerDialog.h"
#include <QVBoxLayout>
#include <QLabel>

ContainerDialog::ContainerDialog(ContainerListModel *model, const QString &contName, QWidget *parent)
    : QDialog(parent), m_model(model), m_contName(contName)
{
    setWindowTitle(contName);
    setLayout(new QVBoxLayout);
    setFixedWidth(400);
    setContentsMargins(0, 0, 0, 0);    
    
    m_destroyButton = new QPushButton("Destroy container");
    m_destroyButton->setStyleSheet("background-color: red");
    m_parameters = new ContainerParametersWidget(m_model, contName);
    QPushButton *doneButton = new QPushButton("Done");
    
    ((QVBoxLayout*)layout())->addWidget(doneButton, 0, Qt::AlignRight);
    layout()->addWidget(m_parameters);    
    layout()->addWidget(m_destroyButton);
    
    connect(doneButton, SIGNAL(pressed()), this, SLOT(accept()));
    connect(m_destroyButton, SIGNAL(pressed()), model, SLOT(destroyContainer(contName)));
}
