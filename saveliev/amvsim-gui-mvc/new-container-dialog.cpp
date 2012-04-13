#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QUrl>
#include <QRegExpValidator>
#include <QMessageBox>

#include "container-delegate.h"
#include "new-container-dialog.h"
#include "main-window.h"

NewContainerDialog::NewContainerDialog(QWidget *parent, DeviceModel *model)
    : QDialog(parent), m_model(model){

    this->setFixedWidth(500);
    this->setStyleSheet("*[left-margin-zero=\"true\"] { margin-left: 0px; }");
    setLayout(new QVBoxLayout);

    initNameEdit();
    initUrlEdit();
    initLocalEdit();
}

void NewContainerDialog::tryCreateHttpFtp() {
    QUrl url = QUrl::fromUserInput(m_urlEdit->text());
    if (!url.isValid()) {
        invalidate(m_urlEdit, m_urlError, "Invalid url");
    } else {
        StorageDescriptor storage;
        storage.address = m_urlEdit->text().toStdString();
        if (url.scheme() == "http") {
            storage.type = StorageDescriptor::Http;
        } else if (url.scheme() == "ftp") {
            storage.type = StorageDescriptor::Ftp;
        } else {
            invalidate(m_urlEdit, m_urlError, "Only http or ftp allowed");
            return;
        }

        // ContainerInfo contInfo(m_nameEdit->text(), storage);
        if (m_model->createContainer(m_nameEdit->text(), storage)) {
            accept();
        }

        invalidate(m_urlEdit, m_urlError, "Error creating a container");
        //if (m_device->createContainer(m_nameEdit->text().toStdString(), storage) < 0) {
    }
}

void NewContainerDialog::invalidate(QLineEdit *edit, QLabel *label, QString msg) {
    edit->setStyleSheet("QLineEdit { border: 1px solid red; }");
    label->setText(msg);
}

void NewContainerDialog::initNameEdit() {
    m_nameEdit = new QLineEdit(this);
    layout()->addWidget(new QLabel("Name of container"));
    layout()->addWidget(m_nameEdit);
}

void NewContainerDialog::initUrlEdit() {
    m_urlEdit = new QLineEdit(this);
    m_urlLoadButton = new QPushButton("Load image by HTTP ir FTP", this);
    m_urlError = new QLabel(this);

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

    QObject::connect(m_urlLoadButton, SIGNAL(clicked()), this, SLOT(tryCreateHttpFtp()));
}

void NewContainerDialog::initLocalEdit() {
    m_localAddressEdit = new QLineEdit(this);
 // m_chooseFileButton(new QPushButton("Choose", this)),
    m_localLoadButton = new QPushButton("Install image from local disk", this);
    m_localError = new QLabel(this);

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

    // QHBoxLayout *localFileLayout = new QHBoxLayout();
    // localFileLayout->addWidget(m_localAddressEdit);
    // localFileLayout->addWidget(new QLabel(" ", this));
    // localFileLayout->addWidget(m_chooseFileButton);
    // localFileLayout->setGeometry(10, 400, 10, 500);

    // QObject::connect(m_localLoadButton, SIGNAL(clicked()), this, SLOT(tryCreate()));
}
