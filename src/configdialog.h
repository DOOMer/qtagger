#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QTextCodec>
#include <QMap>
#include <QDebug>

#include "config.h"

namespace Ui {
    class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

protected:
    void changeEvent(QEvent *e);
    Config *conf;

private:
    Ui::ConfigDialog *ui;
    CfgFlags::ToolbarType toolbarType;

private slots:
    void on_rbText_clicked();
    void on_rbIcon_clicked();
    void on_rbTextIcon_clicked();
    void on_butSave_clicked();
    void on_butCancel_clicked();
};

#endif // CONFIGDIALOG_H
