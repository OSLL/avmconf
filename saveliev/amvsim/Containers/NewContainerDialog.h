#ifndef NEWCONTAINERDIALOG_H
#define NEWCONTAINERDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include "ContainerDelegate.h"
#include "ContainerListModel.h"

namespace Ui {
    class NewContainerDialog;
}

class NewContainerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewContainerDialog(QWidget *parent, ContainerListModel *model);
    ~NewContainerDialog();

private:
    ContainerListModel *m_model;

    Ui::NewContainerDialog *ui;

    void invalidate(QLineEdit *edit, QLabel *label, QString msg);

public slots:
    void tryCreateHttpFtp();
    void tryCreateLocal();
    void chooseFile();
};

#endif // NEWCONTAINERDIALOG_H
