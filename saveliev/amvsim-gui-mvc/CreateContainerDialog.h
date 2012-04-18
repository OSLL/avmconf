#ifndef NEWCONTAINERDIALOG_H
#define NEWCONTAINERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "ContainerDelegate.h"
#include "DeviceModel.h"

namespace Ui {
    class CreateContainerDialog;
}

class MyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent) : QWidget(parent) {}
};

class NewContainerDialog : public QDialog {
    Q_OBJECT

public:
    NewContainerDialog(QWidget *parent, DeviceModel *model);

private:
    void initNameEdit();
    void initUrlEdit();
    void initLocalEdit();

    DeviceModel *m_model;

    QLineEdit *m_nameEdit;

    QLineEdit *m_urlEdit;
    QPushButton *m_urlLoadButton;
    QLabel *m_urlError;

    QLineEdit *m_localAddressEdit;
    QPushButton *m_chooseFileButton;
    QPushButton *m_localLoadButton;
    QLabel *m_localError;

    void invalidate(QLineEdit *edit, QLabel *label, QString msg);

public slots:
    void tryCreateHttpFtp();
    void chooseFile();

signals:
 // void done();
};

#endif // NEWCONTAINERDIALOG_H
