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
#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("qTagger");

    QTranslator localize;

#ifdef Q_WS_X11
    QString localizeFile = PREFIX;
    localizeFile.append("/share/qtagger/localize/qtagger_"+Config::getSysLang()+".qm");
    localize.load(localizeFile);

#endif
#ifdef Q_WS_WIN // QLocale::system().name()
    localize.load(app.applicationDirPath()+"/localize/qtagger_"+Config::getSysLang()+".qm");
#endif

    app.installTranslator(&localize);

#ifdef VERSION
    app.setApplicationVersion(VERSION);
#else
    app.setApplicationVersion("dev");
#endif
    MainWindow w;

    w.show();

    return app.exec();
}
