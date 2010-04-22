#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent), conf(Config::instance()), ui(new Ui::ConfigDialog)

{
    ui->setupUi(this);

    switch(conf->value(KEY_TOOLBAR_DYSPLAY).toInt())
    {
    case CfgFlags::tbTextIcon:
        ui->rbTextIcon->setChecked(true); break;
    case CfgFlags::tbIcon:
        ui->rbIcon->setChecked(true); break;
    case CfgFlags::tbText:
        ui->rbText->setChecked(true); break;
    default:
        ui->rbTextIcon->setChecked(true); break;
    }

    ui->cbxCodecs->setEditable(true);
    ui->cbxCodecs->setEditText(conf->value(KEY_SOURCE_ENCODING).toString());
//        qDebug() << "conf->value(KEY_SOURCE_ENCODING).toString() " << conf->value(KEY_SOURCE_ENCODING).toString();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
    conf = NULL;
    delete conf;
}

void ConfigDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ConfigDialog::on_butCancel_clicked()
{
    reject();
}

void ConfigDialog::on_butSave_clicked()
{
    qDebug() << "select " << toolbarType;
    conf->setValue(KEY_TOOLBAR_DYSPLAY, QVariant(toolbarType));
    qDebug() << "KEY_TOOLBAR_DYSPLAY" << conf->value(KEY_TOOLBAR_DYSPLAY);
    conf->saveSettings();
    accept();
}

void ConfigDialog::on_rbTextIcon_clicked()
{
    toolbarType = CfgFlags::tbTextIcon;
}

void ConfigDialog::on_rbIcon_clicked()
{
    toolbarType = CfgFlags::tbIcon;
}


void ConfigDialog::on_rbText_clicked()
{
    toolbarType = CfgFlags::tbText;
}
