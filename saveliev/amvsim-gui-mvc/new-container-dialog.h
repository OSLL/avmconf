#ifndef NEWCONTAINERDIALOG_H
#define NEWCONTAINERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "container-delegate.h"
#include "device-model.h"

namespace Ui {
    class NewContainerDialog;
}

class WidgetButtonWithError : public QWidget {
    Q_OBJECT

public:
    explicit WidgetButtonWithError(QWidget *parent) : QWidget(parent) {}

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

signals:
 // void done(ContainerInfo);
};

#endif // NEWCONTAINERDIALOG_H
