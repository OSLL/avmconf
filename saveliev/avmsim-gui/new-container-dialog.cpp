
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QUrl>
#include <QRegExpValidator>

#include <QMessageBox>

#include "new-container-dialog.h"
#include "configurator-window.h"
//#include "ui_new-container-dialog.h"

NewContainerDialog::NewContainerDialog(AndroidDevice *device, QWidget *parent) :
    m_device(device),
    QDialog(parent),
    m_nameEdit(new QLineEdit(this)),
    m_urlEdit(new QLineEdit(this)),
    m_urlLoadButton(new QPushButton("Load image by HTTP ir FTP", this)),
    m_urlError(new QLabel(this)),
 // m_ftpAddressEdit(new QLineEdit(this)),
 // m_ftpLoadButton(new QPushButton("Load image by FTP", this)),
    m_localAddressEdit(new QLineEdit(this)),
 // m_chooseFileButton(new QPushButton("Choose", this)),
    m_localLoadButton(new QPushButton("Install image from local disk", this)),
    m_localError(new QLabel(this)) {

    this->setFixedWidth(500);
    this->setStyleSheet("*[left-margin-zero=\"true\"] { margin-left: 0px; }");
    setLayout(new QVBoxLayout);

    layout()->addWidget(new QLabel("Name of container"));
    layout()->addWidget(m_nameEdit);

    QLabel *urlLabel = new QLabel("HTTP or FTP address of image");
    urlLabel->setStyleSheet("margin: 15px 0px 0px -4px");
    layout()->addWidget(urlLabel);
    layout()->addWidget(m_urlEdit);
    m_urlLoadButton->setFixedWidth(200);
    m_urlError->setStyleSheet("color: red");
    WidgetButtonWithError *widgetButtonWithError = new WidgetButtonWithError(this);
    widgetButtonWithError->setLayout(new QHBoxLayout);
    widgetButtonWithError->layout()->addWidget(m_urlLoadButton);
    widgetButtonWithError->layout()->addWidget(m_urlError);
    widgetButtonWithError->layout()->setContentsMargins(0, 0, 0, 0);
    widgetButtonWithError->layout()->setMargin(0);
    widgetButtonWithError->setStyleSheet("WidgetButtonWithError { margin-left: -10px; padding-left: 0px; }");
    layout()->addWidget(widgetButtonWithError);

 // layout()->addWidget(m_urlLoadButton);
 // layout()->addWidget(m_urlError);
 // m_ftpLoadButton->setFixedWidth(150);
 // layout()->addWidget(new QLabel("FTP address of image"));
 // layout()->addWidget(m_ftpAddressEdit);
 // layout()->addWidget(m_ftpLoadButton);

 // QHBoxLayout *localFileLayout = new QHBoxLayout();
 // localFileLayout->addWidget(m_localAddressEdit);
 // localFileLayout->addWidget(new QLabel(" ", this));
 // localFileLayout->addWidget(m_chooseFileButton);
 // localFileLayout->setGeometry(10, 400, 10, 500);    

    QLabel *localLabel = new QLabel("Local address of image");
    localLabel->setStyleSheet("margin: 15px 0px 0px -4px");
    layout()->addWidget(localLabel);
    layout()->addWidget(m_localAddressEdit);
    m_localLoadButton->setFixedWidth(210);
    m_localError->setStyleSheet("color: red");
    WidgetButtonWithError *loadBwE = new WidgetButtonWithError(this);
    loadBwE->setLayout(new QHBoxLayout);
    loadBwE->layout()->addWidget(m_localLoadButton);
    loadBwE->layout()->addWidget(m_localError);
    loadBwE->layout()->setContentsMargins(0, 0, 0, 0);
    loadBwE->layout()->setMargin(0);
    loadBwE->setStyleSheet("WidgetButtonWithError { margin-left: -10px; padding-left: 0px; }");
    layout()->addWidget(loadBwE);

    QObject::connect(m_urlLoadButton, SIGNAL(clicked()), this, SLOT(tryCreateHttpFtp()));
 // QObject::connect(m_localLoadButton, SIGNAL(clicked()), this, SLOT(tryCreate()));
}

void NewContainerDialog::tryCreateHttpFtp() {
    QUrl url = QUrl::fromUserInput(m_urlEdit->text());
    if (!url.isValid()) {
        invalidate(m_urlEdit, m_urlError, "Invalid url");
    } else {
        StorageDescriptor storage(m_urlEdit->text().toStdString());
        if (url.scheme() == "http") {
            storage.setType(StorageDescriptor::Http);
        } else if (url.scheme() == "ftp") {
            storage.setType(StorageDescriptor::Ftp);
        } else {
            invalidate(m_urlEdit, m_urlError, "Only http or ftp allowed");
        }

        if (m_device->createContainer(m_nameEdit->text().toStdString(), storage) < 0) {
            invalidate(m_urlEdit, m_urlError, "Error creating a container");
        } else {
            // QMessageBox::information(0, "Information", "accepted " + url.toString());
            accept();
        }
    }
}

void NewContainerDialog::invalidate(QLineEdit *edit, QLabel *label, QString msg) {
    edit->setStyleSheet("QLineEdit { border: 1px solid red; }");
    label->setText(msg);
}



//NewContainerDialog::~NewContainerDialog() {
//    delete m_ui;
//}

