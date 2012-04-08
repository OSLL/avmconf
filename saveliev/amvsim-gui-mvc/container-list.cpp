#include <QVBoxLayout>
#include "container-list.h"

ContainerList::ContainerList(QWidget *parent) : QWidget(parent) {
    setLayout(new QVBoxLayout());
    m_view = new QListView();

}
