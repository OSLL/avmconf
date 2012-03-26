#ifndef NEWCONTAINERDIALOG_H
#define NEWCONTAINERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "api/AndroidDevice.h"

namespace Ui {
    class NewContainerDialog;
}

class NewContainerDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewContainerDialog(AndroidDevice *device, QWidget *parent = 0);
 // ~NewContainerDialog();
    const std::string& getHttpAddress();

private:
 // Ui::NewContainerDialog *m_ui;
    AndroidDevice *m_device;

    QLineEdit *m_httpAddressEdit;
    QPushButton *m_httpLoadButton;

    QLineEdit *m_ftpAddressEdit;
    QPushButton *m_ftpLoadButton;

    QLineEdit *m_localAddressEdit;
    QPushButton *m_chooseFileButton;
    QPushButton *m_localLoadButton;

public slots:
    void tryCreate();
};

#endif // NEWCONTAINERDIALOG_H
