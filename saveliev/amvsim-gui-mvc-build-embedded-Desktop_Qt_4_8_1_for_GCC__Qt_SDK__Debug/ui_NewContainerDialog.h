/********************************************************************************
** Form generated from reading UI file 'NewContainerDialog.ui'
**
** Created: Wed May 23 17:06:26 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCONTAINERDIALOG_H
#define UI_NEWCONTAINERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewContainerDialog
{
public:
    QLabel *nameLabel;
    QLabel *urlLabel;
    QLineEdit *nameEdit;
    QLineEdit *urlEdit;
    QPushButton *loadUrlButton;
    QLabel *urlError;
    QLineEdit *localEdit;
    QLabel *localLabel;
    QLabel *localError;
    QPushButton *loadLocalButton;
    QPushButton *chooseButton;

    void setupUi(QDialog *NewContainerDialog)
    {
        if (NewContainerDialog->objectName().isEmpty())
            NewContainerDialog->setObjectName(QString::fromUtf8("NewContainerDialog"));
        NewContainerDialog->resize(531, 294);
        nameLabel = new QLabel(NewContainerDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(20, 20, 211, 16));
        urlLabel = new QLabel(NewContainerDialog);
        urlLabel->setObjectName(QString::fromUtf8("urlLabel"));
        urlLabel->setGeometry(QRect(20, 90, 231, 16));
        nameEdit = new QLineEdit(NewContainerDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(20, 40, 491, 22));
        urlEdit = new QLineEdit(NewContainerDialog);
        urlEdit->setObjectName(QString::fromUtf8("urlEdit"));
        urlEdit->setGeometry(QRect(20, 110, 491, 22));
        loadUrlButton = new QPushButton(NewContainerDialog);
        loadUrlButton->setObjectName(QString::fromUtf8("loadUrlButton"));
        loadUrlButton->setGeometry(QRect(14, 140, 215, 32));
        urlError = new QLabel(NewContainerDialog);
        urlError->setObjectName(QString::fromUtf8("urlError"));
        urlError->setGeometry(QRect(230, 144, 281, 20));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(69, 69, 69, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        urlError->setPalette(palette);
        localEdit = new QLineEdit(NewContainerDialog);
        localEdit->setObjectName(QString::fromUtf8("localEdit"));
        localEdit->setGeometry(QRect(20, 220, 401, 22));
        localLabel = new QLabel(NewContainerDialog);
        localLabel->setObjectName(QString::fromUtf8("localLabel"));
        localLabel->setGeometry(QRect(20, 200, 231, 16));
        localError = new QLabel(NewContainerDialog);
        localError->setObjectName(QString::fromUtf8("localError"));
        localError->setGeometry(QRect(230, 254, 281, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        localError->setPalette(palette1);
        loadLocalButton = new QPushButton(NewContainerDialog);
        loadLocalButton->setObjectName(QString::fromUtf8("loadLocalButton"));
        loadLocalButton->setGeometry(QRect(14, 250, 221, 32));
        chooseButton = new QPushButton(NewContainerDialog);
        chooseButton->setObjectName(QString::fromUtf8("chooseButton"));
        chooseButton->setGeometry(QRect(426, 216, 91, 32));

        retranslateUi(NewContainerDialog);

        QMetaObject::connectSlotsByName(NewContainerDialog);
    } // setupUi

    void retranslateUi(QDialog *NewContainerDialog)
    {
        NewContainerDialog->setWindowTitle(QApplication::translate("NewContainerDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("NewContainerDialog", "Name of container", 0, QApplication::UnicodeUTF8));
        urlLabel->setText(QApplication::translate("NewContainerDialog", "HTTP of FTP address of image", 0, QApplication::UnicodeUTF8));
        loadUrlButton->setText(QApplication::translate("NewContainerDialog", "Load image by HTTP or FTP", 0, QApplication::UnicodeUTF8));
        urlError->setText(QString());
        localLabel->setText(QApplication::translate("NewContainerDialog", "Local address of image", 0, QApplication::UnicodeUTF8));
        localError->setText(QString());
        loadLocalButton->setText(QApplication::translate("NewContainerDialog", "Install image from local disk", 0, QApplication::UnicodeUTF8));
        chooseButton->setText(QApplication::translate("NewContainerDialog", "Choose", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewContainerDialog: public Ui_NewContainerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCONTAINERDIALOG_H
