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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
//#include <QRect>
#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QItemSelection>

#include "qtagger.h"
#include "tag.h"
#include "trackfileitem.h"
#include "trackmodel.h"
#include "aboutdialog.h"
#include "configdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);    

private:    
    Ui::MainWindow *ui;
    QTagger *app;
    QAction *actAddFiles;
    QAction *actAddDir;
    QAction *actToUnicode;
    QAction *actRemove;
    QAction *actClear;
    QAction *actSettings;
    QAction *actAbout;
    QAction *actAboutQt;
    QAction *actQuit;

    QMenu *menuFile;
    QMenu *menuHelp;

    TrackModel *model;

    Tag *tag;

    void createActions();
    void clearEditBoxes();

    const QString SELECT_ALL;
    const QString SELECT_NONE;

private slots:
    void on_butSelect_clicked();
    void on_butSave_clicked();
    void on_butCancel_clicked();
    void on_treeView_clicked(QModelIndex index);
    void slotExit();
    void slotAbout();
    void slotAboutQt();
    void slotAddFiles();
    void slotAddDir();
    void slotToUnicode();
    void slotRemoveFiles();
    void slotClear();
    void slotSettings();
    void slotTreeSelChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // MAINWINDOW_H
