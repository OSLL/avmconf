#ifndef NEWCONTAINERDIALOG_H
#define NEWCONTAINERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "api/AndroidDevice.h"

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
    explicit NewContainerDialog(AndroidDevice *device, QWidget *parent = 0);
 // ~NewContainerDialog();
    const std::string& getUrl();

private:
 // Ui::NewContainerDialog *m_ui;
    AndroidDevice *m_device;

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
};

#endif // NEWCONTAINERDIALOG_H
