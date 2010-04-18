#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
//#include <QRect>
//#include <QDesktopWidget>
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QDebug>

#include "qtagger.h"
#include "tag.h"
#include "trackfileitem.h"
#include "trackmodel.h"
#include "aboutdialog.h"
#include <QTextCodec>

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

private slots:
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
};

#endif // MAINWINDOW_H
