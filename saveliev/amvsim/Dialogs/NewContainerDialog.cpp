
#include <QFileDialog>
#include <QUrl>

#include "NewContainerDialog.h"
#include "ui_NewContainerDialog.h"


NewContainerDialog::NewContainerDialog(QWidget *parent, ContainerListModel *model)
    : QDialog(parent),
      m_model(model),
      ui(new Ui::NewContainerDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->chooseButton,    SIGNAL(clicked()), this, SLOT(chooseFile()));
    QObject::connect(ui->loadUrlButton,   SIGNAL(clicked()), this, SLOT(tryCreateHttpFtp()));
    QObject::connect(ui->loadLocalButton, SIGNAL(clicked()), this, SLOT(tryCreateLocal()));
}


NewContainerDialog::~NewContainerDialog()
{
    delete ui;
}


void NewContainerDialog::invalidate(QLineEdit *edit, QLabel *label, QString msg)
{
    edit->setStyleSheet("QLineEdit { border: 1px solid red; }");
    label->setText(msg);
}


void NewContainerDialog::tryCreateHttpFtp()
{
    QUrl url = QUrl::fromUserInput(ui->urlEdit->text());
    if (!url.isValid()) {
        invalidate(ui->urlEdit, ui->urlError, "Invalid url " + ui->urlEdit->text());
    } else {
        StorageDescriptor storage;
        storage.address = ui->urlEdit->text().toStdString();

        if (url.scheme() != "http" && url.scheme() != "ftp") {
            invalidate(ui->urlEdit, ui->urlError, "Only http or ftp are allowed");
        } else {
            if (url.scheme() == "ftp") {
                storage.type = StorageDescriptor::Http;
            } else if (url.scheme() == "ftp") {
                storage.type = StorageDescriptor::Ftp;
            }

            if (m_model->createContainer(ui->nameEdit->text(), storage) < 0) {
                invalidate(ui->urlEdit, ui->urlError, "Error creating a container");
            } else {
                accept();
            }
        }
    }
}

void NewContainerDialog::tryCreateLocal()
{
    QUrl url = QUrl::fromUserInput(ui->urlEdit->text());
    if (!url.isValid()) {
        invalidate(ui->urlEdit, ui->urlError, "Invalid url " + ui->urlEdit->text());
    } else {
        StorageDescriptor storage;
        storage.address = ui->localEdit->text().toStdString();
        
        if (url.scheme() != "file" || url.scheme() != "") {
            invalidate(ui->urlEdit, ui->urlError, "Not a local file");            
        } else {
            storage.type = StorageDescriptor::Local;            
        }
        
        if (m_model->createContainer(ui->nameEdit->text(), storage) < 0) {
            invalidate(ui->localEdit, ui->localError, "Error creating a container");
        } else {
            accept();
        }
    }    
}


void NewContainerDialog::chooseFile()
{
    ui->localEdit->setText(QFileDialog::getOpenFileName(this, "Choose Image", "", "Files (*.*)"));
}

