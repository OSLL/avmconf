
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QUrl>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QFileDialog>

#include "ContainerDelegate.h"
#include "CreateContainerDialog.h"
#include "MainWindow.h"

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
        invalidate(m_urlEdit, m_urlError, "Invalid url " + m_urlEdit->text());
    } else {
        StorageDescriptor storage;
        storage.address = m_urlEdit->text().toStdString();

        if (url.scheme() != "http" && url.scheme() != "ftp") {
            invalidate(m_urlEdit, m_urlError, "Only http or ftp are allowed");
        } else {
            if (url.scheme() == "ftp") {
                storage.type = StorageDescriptor::Http;
            } else if (url.scheme() == "ftp") {
                storage.type = StorageDescriptor::Ftp;
            }

            if (m_model->createContainer(m_nameEdit->text(), storage) < 0) {
                invalidate(m_urlEdit, m_urlError, "Error creating a container");
            } else {
                accept();
            }
        }
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
    QLabel *urlLabel = new QLabel("HTTP or FTP address of image");
    urlLabel->setStyleSheet("margin: 15px 0px 0px -4px");

    m_urlEdit = new QLineEdit(this);

    m_urlLoadButton = new QPushButton("Load image by HTTP ir FTP", this);
    m_urlLoadButton->setFixedWidth(200);
    QObject::connect(m_urlLoadButton, SIGNAL(clicked()), this, SLOT(tryCreateHttpFtp()));

    m_urlError = new QLabel(this);
    m_urlError->setStyleSheet("color: red");

    MyWidget *widgetButtonWithError = new MyWidget(this);
    widgetButtonWithError->setLayout(new QHBoxLayout);
    widgetButtonWithError->layout()->addWidget(m_urlLoadButton);
    widgetButtonWithError->layout()->addWidget(m_urlError);
    widgetButtonWithError->layout()->setContentsMargins(0, 0, 0, 0);
    widgetButtonWithError->layout()->setMargin(0);
    widgetButtonWithError->setStyleSheet("MyWidget { margin-left: -10px; padding-left: 0px; }");

    layout()->addWidget(urlLabel);
    layout()->addWidget(m_urlEdit);
    layout()->addWidget(widgetButtonWithError);
}

void NewContainerDialog::initLocalEdit() {    
    QLabel *localLabel = new QLabel("Local address of image");
    localLabel->setStyleSheet("margin: 15px 0px 0px -4px");

    m_localAddressEdit = new QLineEdit(this);

    m_chooseFileButton = new QPushButton("Choose", this);
    QObject::connect(m_chooseFileButton, SIGNAL(clicked()), this, SLOT(chooseFile()));

    MyWidget *chooseFileWidget = new MyWidget(this);
    chooseFileWidget->setStyleSheet("MyWidget#chooseFileWidget { margin: 0px 0px 0px -10px; padding-left: 0px; }");
    chooseFileWidget->setContentsMargins(0, 0, 0 ,0);
    chooseFileWidget->setLayout(new QHBoxLayout);
    chooseFileWidget->layout()->addWidget(m_localAddressEdit);
    chooseFileWidget->layout()->addWidget(m_chooseFileButton);

    m_localLoadButton = new QPushButton("Install image from local disk", this);
    m_localLoadButton->setFixedWidth(210);

    m_localError = new QLabel(this);
    m_localError->setStyleSheet("color: red");

    MyWidget *loadBwE = new MyWidget(this);
    loadBwE->setLayout(new QHBoxLayout);
    loadBwE->layout()->addWidget(m_localLoadButton);
    loadBwE->layout()->addWidget(m_localError);
    loadBwE->layout()->setContentsMargins(0, 0, 0, 0);
    loadBwE->layout()->setMargin(0);

    loadBwE->setStyleSheet("WidgetButtonWithError { margin-left: -10px; padding-left: 0px; }");

    layout()->addWidget(localLabel);
    layout()->addWidget(chooseFileWidget);
    layout()->addWidget(loadBwE);

    // QHBoxLayout *localFileLayout = new QHBoxLayout();
    // localFileLayout->addWidget(m_localAddressEdit);
    // localFileLayout->addWidget(new QLabel(" ", this));
    // localFileLayout->addWidget(m_chooseFileButton);
    // localFileLayout->setGeometry(10, 400, 10, 500);

    // QObject::connect(m_localLoadButton, SIGNAL(clicked()), this, SLOT(tryCreate()));
}

void NewContainerDialog::chooseFile() {
    m_localAddressEdit->setText(QFileDialog::getOpenFileName(this, "Choose Image", "", "Files (*.*)"));
}
