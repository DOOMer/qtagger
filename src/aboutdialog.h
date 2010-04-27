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
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
    class aboutdialog;
}

/**
 * About dialog class
 */
class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor for about dialog
     */
    explicit AboutDialog(QWidget *parent = 0);

    /**
     * Destructor for about dialog
     */
    ~AboutDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::aboutdialog *ui;

private slots:
    /**
     * Close about dialog function
     */
    void on_butClose_clicked();
};

#endif // ABOUTDIALOG_H
