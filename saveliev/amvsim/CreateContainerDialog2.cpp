//#include "CreateContainerDialog2.h"

//CreateContainerDialog2::CreateContainerDialog2(QWidget *parent, DeviceModel *model)
//    : QDialog(parent), m_model(model), ui(new Ui::CreateContainerDialogDialog2)
//{
//    ui->setupUi(this);
//}

//CreateContainerDialog2::~CreateContainerDialog2()
//{
//    delete ui;
//}


//void CreateContainerDialog2::invalidate(QLineEdit *edit, QLabel *label, QString msg)
//{
//    edit->setStyleSheet("QLineEdit { border: 1px solid red; }");
//    label->setText(msg);
//}


//void CreateContainerDialog2::tryCreateHttpFtp()
//{
//    QUrl url = QUrl::fromUserInput(ui->urlEdit->text());
//    if (!url.isValid()) {
//        invalidate(ui->urlEdit, ui->urlError, "Invalid url " + ui->urlEdit->text());
//    } else {
//        StorageDescriptor storage;
//        storage.address = ui->urlEdit->text().toStdString();

//        if (url.scheme() != "http" && url.scheme() != "ftp") {
//            invalidate(ui->urlEdit, ui->urlError, "Only http or ftp are allowed");
//        } else {
//            if (url.scheme() == "ftp") {
//                storage.type = StorageDescriptor::Http;
//            } else if (url.scheme() == "ftp") {
//                storage.type = StorageDescriptor::Ftp;
//            }

//            if (m_model->createContainer(ui->nameEdit->text(), storage) < 0) {
//                invalidate(ui->urlEdit, ui->urlError, "Error creating a container");
//            } else {
//                accept();
//            }
//        }
//    }
//}


//void CreateContainerDialog2::chooseFile()
//{
//    ui->localAddressEdit->setText(QFileDialog::getOpenFileName(this, "Choose Image", "", "Files (*.*)"));
//}

