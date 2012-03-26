
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "new-container-dialog.h"
#include "configurator-window.h"
//#include "ui_new-container-dialog.h"

NewContainerDialog::NewContainerDialog(AndroidDevice *device, QWidget *parent) :
    m_device(device),
    QDialog(parent),
    m_httpAddressEdit(new QLineEdit(this)),
    m_httpLoadButton(new QPushButton("Load image by HTTP", this)),
    m_ftpAddressEdit(new QLineEdit(this)),
    m_ftpLoadButton(new QPushButton("Load image by FTP", this)),
    m_localAddressEdit(new QLineEdit(this)),
 // m_chooseFileButton(new QPushButton("Choose", this)),
    m_localLoadButton(new QPushButton("Install image from local disk", this)) {
    //, m_ui(new Ui::NewContainerDialog) {

 // ui->setupUi(this);

    this->setFixedWidth(500);
    setLayout(new QVBoxLayout);

    m_httpLoadButton->setFixedWidth(160);
    layout()->addWidget(new QLabel("URL address of image"));
    layout()->addWidget(m_httpAddressEdit);
    layout()->addWidget(m_httpLoadButton);

    m_ftpLoadButton->setFixedWidth(150);
    layout()->addWidget(new QLabel("FTP address of image"));
    layout()->addWidget(m_ftpAddressEdit);
    layout()->addWidget(m_ftpLoadButton);

 // QHBoxLayout *localFileLayout = new QHBoxLayout();
 // localFileLayout->addWidget(m_localAddressEdit);
 // localFileLayout->addWidget(new QLabel(" ", this));
 // localFileLayout->addWidget(m_chooseFileButton);
 // localFileLayout->setGeometry(10, 400, 10, 500);
    m_localLoadButton->setFixedWidth(210);
    layout()->addWidget(new QLabel("Local address of image"));
    layout()->addWidget(m_localAddressEdit);
    layout()->addWidget(m_localLoadButton);

    QObject::connect(m_httpLoadButton, SIGNAL(clicked()), this, SLOT(tryCreate()));
    QObject::connect(m_ftpLoadButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(m_localLoadButton, SIGNAL(clicked()), this, SLOT(close()));
}

const std::string & NewContainerDialog::getHttpAddress() {
    return m_httpAddressEdit->text().toStdString();
}

void NewContainerDialog::tryCreate() {
    StorageDescriptor *storage;
    if (sender() == m_httpLoadButton) {
        storage = new HttpURLStorageDescriptor(getHttpAddress());
        // если некорректно создалось, подсветить и написать
    } else {
        return;
    }

    if (m_device->createContainer("Android 1", *storage) == 0) {
        accept();
    } else {

    }
}


//NewContainerDialog::~NewContainerDialog() {
//    delete m_ui;
//}

