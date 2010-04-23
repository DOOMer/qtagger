#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent), conf(Config::instance()), ui(new Ui::ConfigDialog)

{
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName() + " - " + tr("Settings"));
    switch(conf->value(KEY_TOOLBAR_DYSPLAY).toInt())
    {
    case CfgFlags::tbTextIcon:
        {
            ui->rbTextIcon->setChecked(true);
            toolbarType = CfgFlags::tbTextIcon;
            break;
        }
    case CfgFlags::tbIcon:
        {
            ui->rbIcon->setChecked(true);
            toolbarType = CfgFlags::tbIcon;
            break;
        }
    case CfgFlags::tbText:
        {
            ui->rbText->setChecked(true);
            toolbarType = CfgFlags::tbText;
            break;
        }
    default:
        ui->rbTextIcon->setChecked(true);
        toolbarType = CfgFlags::tbTextIcon;
        break;
    }

    QList<QTextCodec *> codecs;



    // codecs
    QMap<QString, QTextCodec *> codecMap;

    foreach (int mib, QTextCodec::availableMibs())
    {
        QTextCodec *codec = QTextCodec::codecForMib(mib);

        QString sortKey = codec->name().toUpper();

        codecMap.insert(sortKey, codec);
    }
    codecs = codecMap.values();

    // iserting combobox items
    foreach (QTextCodec *codec, codecs)
    {
        ui->cbxCodecs->addItem(codec->name(), codec->mibEnum());
    }

//    ui->cbxCodecs->setEditable(true);
    QString seletedCodec = conf->value(KEY_SOURCE_ENCODING).toString();
    ui->cbxCodecs->setCurrentIndex(ui->cbxCodecs->findText(seletedCodec));
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

    qDebug() << ui->cbxCodecs->currentText();
    conf->setValue(KEY_SOURCE_ENCODING, QVariant(ui->cbxCodecs->currentText()));
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
