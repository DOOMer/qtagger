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
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    app(new QTagger), SELECT_ALL(tr("Select all")), SELECT_NONE(tr("Select none"))
{    
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName());
    updateUI();
    createActions();
    model = new TrackModel(this);

    ui->treeView->setModel(app->getTrackModel());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete app;
}

void MainWindow::createActions()
{
    actAddFiles = new QAction(tr("Add Files"), this);
    actAddDir = new QAction(tr("Add Dir"), this);
    actToUnicode = new QAction(tr("To Unicode"), this);
    actRemove = new QAction(tr("Remover"), this);
    actClear = new QAction(tr("Clear"), this);
    actSettings = new QAction(tr("Settings"), this);
    actAbout = new QAction(tr("About"), this);
    actAboutQt = new QAction(tr("About Qt"), this);
    actQuit = new QAction(tr("Exit"), this);

    actToUnicode->setEnabled(false);
    actClear->setEnabled(false);
    actRemove->setEnabled(false);

    ui->mainToolBar->addAction(actAddDir);
    ui->mainToolBar->addAction(actAddFiles);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actToUnicode);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actRemove);
    ui->mainToolBar->addAction(actClear);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actSettings);
    ui->mainToolBar->addAction(actAbout);

    menuFile = new QMenu(tr("File"), this);
    menuHelp = new QMenu(tr("Help"), this);
    menuTrackContext = new QMenu(this);

    menuFile->addAction(actAddFiles);
    menuFile->addAction(actAddDir);
    menuFile->addSeparator();
    menuFile->addAction(actToUnicode);
    menuFile->addSeparator();
    menuFile->addAction(actRemove);
    menuFile->addAction(actClear);
    menuFile->addSeparator();
    menuFile->addAction(actSettings);
    menuFile->addSeparator();
    menuFile->addAction(actQuit);

    menuHelp->addAction(actAbout);
    menuHelp->addAction(actAboutQt);

    ui->menuBar->addMenu(menuFile);
    ui->menuBar->addMenu(menuHelp);

    menuTrackContext->addAction(actAddDir);
    menuTrackContext->addAction(actAddFiles);
    menuTrackContext->addSeparator();
    menuTrackContext->addAction(actToUnicode);
    menuTrackContext->addSeparator();
    menuTrackContext->addAction(actRemove);
    menuTrackContext->addAction(actClear);

    ui->editYear->setValidator(new QIntValidator(this));
    ui->editTrackNum->setValidator(new QIntValidator(this));

    ui->butSelect->setText(SELECT_ALL);

    // connects actions
    connect(actAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(actAboutQt, SIGNAL(triggered()), this, SLOT(slotAboutQt()));
    connect(actQuit, SIGNAL(triggered()), this, SLOT(slotExit()));
    connect(actAddDir, SIGNAL(triggered()), this, SLOT(slotAddDir()));
    connect(actAddFiles, SIGNAL(triggered()), this, SLOT(slotAddFiles()));
    connect(actRemove, SIGNAL(triggered()), this, SLOT(slotRemoveFiles()));
    connect(actClear, SIGNAL(triggered()), this, SLOT(slotClear()));
    connect(actSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));
    connect(actToUnicode, SIGNAL(triggered()), this, SLOT(slotToUnicode()));    
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::slotExit()
{
    qApp->quit();
}

void MainWindow::slotAbout()
{    
    AboutDialog * about = new AboutDialog;

    about->exec();

    delete about;
}

void MainWindow::slotAboutQt()
{
    qApp->aboutQt();
}

void MainWindow::slotAddFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Open File"), app->lastAddedDir());

    app->addFiles(fileList);

    actClear->setEnabled(true);
    ui->butSelect->setEnabled(true);

    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(slotTreeSelChanged(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::slotAddDir()
{
    QDir addingDir = QFileDialog::getExistingDirectory(this, tr("Add directory"), app->lastAddedDir(), QFileDialog::ShowDirsOnly);

    app->iterateDir(addingDir);

    actClear->setEnabled(true);
    ui->butSelect->setEnabled(true);

    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(slotTreeSelChanged(const QItemSelection &, const QItemSelection &)));
}


void MainWindow::slotToUnicode()
{
    QModelIndexList selected = ui->treeView->selectionModel()->selectedRows();
    if (app->toUnicode(selected) == true)
    {
        ui->treeView->clearSelection();
    }
}

void MainWindow::slotRemoveFiles()
{    
    QModelIndexList selected = ui->treeView->selectionModel()->selectedRows();
//    quint8 num = selected.count();
//    // show messagebox
//    QMessageBox msg(QMessageBox::Question,
//                    tr("Delete selected") + QString(" - qTagger"), "" ,
//                    QMessageBox::Yes | QMessageBox::No);
//    msg.setText(tr("Delete selected tracks"));
//    msg.setInformativeText(tr("Do yo want delete selected ") + QString::number(num) + tr(" track(s)?"));

//    int result = msg.exec();

//    if (result == QMessageBox::Yes)
//    {

    app->removeFiles(selected);

    ui->treeView->clearSelection();

    if (app->getTrackModel()->rowCount() == 0)
    {
        actToUnicode->setEnabled(false);
        actClear->setEnabled(false);
        actRemove->setEnabled(false);
        ui->butSelect->setEnabled(false);

        disconnect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(slotTreeSelChanged(const QItemSelection &, const QItemSelection &)));
    }
//    }
}

void MainWindow::slotClear()
{
    // show messagebox
//    QMessageBox msg(QMessageBox::Question,
//                    tr("Clear list") + QString(" - qTagger"), "" ,
//                    QMessageBox::Yes | QMessageBox::No);
//    msg.setText(tr("Clear track list"));
//    msg.setInformativeText(tr("Do yo want clear track list?"));

//    int result = msg.exec();

//    if (result == QMessageBox::Yes)
//    {
    app->clearList();

    actToUnicode->setEnabled(false);
    actClear->setEnabled(false);
    actRemove->setEnabled(false);
    ui->butSelect->setEnabled(false);

    disconnect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(slotTreeSelChanged(const QItemSelection &, const QItemSelection &)));
//    }
}

void MainWindow::slotSettings()
{
    ConfigDialog *configdialog = new ConfigDialog;

    quint8 resilt = configdialog->exec();
    if (resilt == QDialog::Accepted)
    {
        updateUI();
    }

    delete configdialog;
}

void MainWindow::updateUI()
{
    int tbType = app->config()->value(KEY_TOOLBAR_DYSPLAY).toUInt();

    switch (tbType)
    {
    case CfgFlags::tbTextIcon:
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); break;
    case CfgFlags::tbIcon:
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly); break;
    case CfgFlags::tbText:
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextOnly); break;
    default:
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); break;
    }
}

void MainWindow::on_treeView_clicked(QModelIndex index)
{
    app->currentTag()->setFile(app->getTrackModel()->getItem(index.row())->getFile());
    ui->editTitle->setText(app->currentTag()->toUtfTagStr(app->currentTag()->title()));
    ui->editAlbum->setText(app->currentTag()->toUtfTagStr(app->currentTag()->album()));
    ui->editaArtist->setText(app->currentTag()->toUtfTagStr(app->currentTag()->artist()));
    ui->editYear->setText(QString::number(app->currentTag()->year()));
    ui->cbxGenre->setEditText(app->currentTag()->toUtfTagStr(app->currentTag()->genre()));

    // TODO -- create genrelist & select in list
    ui->editTrackNum->setText(QString::number(app->currentTag()->trackNum()));
    ui->editComment->setPlainText(app->currentTag()->toUtfTagStr(app->currentTag()->comment()));

    ui->labBitrate->setText(tr("Bitrate: ") + QString::number(app->currentTag()->audio->bitrate()) + " kbps");
    ui->labSampleRate->setText(tr("Sample rate: ") + QString::number(app->currentTag()->audio->sampleRate()) + " Hz");
        ui->labTime->setText(tr("Time: ") + app->currentTag()->audio->timeStr());
}

void MainWindow::on_butCancel_clicked()
{
    ui->editTitle->setText(app->currentTag()->title());
    ui->editAlbum->setText(app->currentTag()->album());
    ui->editaArtist->setText(app->currentTag()->artist());
    ui->editYear->setText(QString::number(app->currentTag()->year()));
    ui->cbxGenre->setEditText(app->currentTag()->genre());;
    // TODO -- create genrelist & select in list
    ui->editTrackNum->setText(QString::number(app->currentTag()->trackNum()));
    ui->editComment->setPlainText(app->currentTag()->comment());
}

void MainWindow::on_butSave_clicked()
{
    app->currentTag()->setAlbum(ui->editAlbum->text());
    app->currentTag()->setArtist(ui->editaArtist->text());
    app->currentTag()->setTitle(ui->editTitle->text());
    app->currentTag()->setGenre(ui->cbxGenre->currentText());
    app->currentTag()->setComment(ui->editComment->toPlainText());
    app->currentTag()->setYear(ui->editYear->text().toInt());
    app->currentTag()->setTrackNum(ui->editTrackNum->text().toInt());

    if (app->currentTag()->writeInfo() == true)
    {
        QModelIndex selected = ui->treeView->currentIndex();
        if (app->updateItem(selected) == true)
        {
            // clear selection
            clearEditBoxes();
            ui->treeView->clearSelection();
        }
    }
    else
    {
        qDebug() << "false saving";
    }
}

void MainWindow::slotTreeSelChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (selected.isEmpty() == true)
    {
        actToUnicode->setEnabled(false);

        actRemove->setEnabled(false);
        clearEditBoxes();
        ui->butSelect->setText(SELECT_ALL);
    }
    else
    {
        actToUnicode->setEnabled(true);
        actClear->setEnabled(true);
        actRemove->setEnabled(true);
        ui->butSelect->setText(SELECT_NONE);
    }
}

void MainWindow::clearEditBoxes()
{
    ui->editaArtist->clear();
    ui->editAlbum->clear();
    ui->editComment->clear();
    ui->editTitle->clear();
    ui->editTrackNum->clear();
    ui->editYear->clear();

    ui->labBitrate->clear();
    ui->labSampleRate->clear();
    ui->labTime->clear();
}

void MainWindow::on_butSelect_clicked()
{
    bool selected = ui->treeView->selectionModel()->selection().isEmpty();

    if (selected == true)
    {
        ui->treeView->selectAll();
    }
    else
    {
        ui->treeView->clearSelection();
    }
}

// executing context menu on track list
void MainWindow::on_treeView_customContextMenuRequested(QPoint pos)
{
    QWidget* w = static_cast<QWidget*>(QObject::sender());
    menuTrackContext->exec(w->mapToGlobal(pos));
}
