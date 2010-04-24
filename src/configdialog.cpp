/***************************************************************************
 *   Copyright (C) 2010 by Artem 'DOOMer' Galichkin                        *
 *   doomer3d@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
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
    conf->setValue(KEY_TOOLBAR_DYSPLAY, QVariant(toolbarType));

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
