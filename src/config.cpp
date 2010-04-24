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
#include "config.h"

Config* Config::ptrInstance = 0;

Config::Config()
{
    loadSettings();
}

Config* Config::instance()
{
    if (!ptrInstance)
    {        
        ptrInstance = new Config;
    }

    return ptrInstance;
}

void Config::killInstance()
{
    if (ptrInstance)
    {
        delete ptrInstance;
        ptrInstance = 0;
    }
}

QString Config::configFile()
{
    QString path;
    path.append(QDir::homePath());
    path.append(QDir::separator());
    path.append(".config/qtagger/qtagger.conf");

    return path;
}

void Config::loadSettings()
{
    // check existing file
    if (QFile::exists(Config::configFile()) == false)
    {
        defaultSettings();
    }
    else
    {
        QSettings loader(Config::configFile().toAscii(), QSettings::IniFormat);

        loader.beginGroup("Main");
        confData.insert(KEY_SOURCE_ENCODING, loader.value(KEY_SOURCE_ENCODING, DEFAULT_ENCODING).toString());
        loader.endGroup();;
        loader.beginGroup("Display");
        confData.insert(KEY_TOOLBAR_DYSPLAY, loader.value(KEY_TOOLBAR_DYSPLAY, DEFAULT_TOOLBAR_TYPE));
        loader.endGroup();;
    }
}

void Config::saveSettings()
{
    QSettings saver(Config::configFile().toAscii(), QSettings::IniFormat);

    // write settings
    saver.beginGroup("Main");
    saver.setValue(KEY_SOURCE_ENCODING, confData[KEY_SOURCE_ENCODING].toString());
    saver.endGroup();;

    saver.beginGroup("Display");
    saver.setValue(KEY_TOOLBAR_DYSPLAY, confData[KEY_TOOLBAR_DYSPLAY].toUInt());
    saver.endGroup();;
}

void Config::defaultSettings()
{
    setValue(KEY_SOURCE_ENCODING, QVariant(DEFAULT_ENCODING));
    setValue(KEY_TOOLBAR_DYSPLAY, QVariant(DEFAULT_TOOLBAR_TYPE));

    saveSettings();
}

void Config::setValue(const QString &key, QVariant val)
{
    confData[key] = val;
}

QVariant Config::value(const QString &key)
{
//    QVariant ref = &confData[key];
    return confData[key];
}

QString Config::getSysLang()
{
#ifdef Q_WS_X11
    QByteArray lang = qgetenv("LC_ALL");

    if (lang.isEmpty())
    {
        lang = qgetenv("LC_MESSAGES");
    }
    if (lang.isEmpty())
    {
        lang = qgetenv("LANG");
    }
    if (!lang.isEmpty())
    {
        return QLocale (lang).name();
    }
    else
    {
        return  QLocale::system().name();
    }
#endif
#ifdef Q_WS_WIN
    return  QLocale::system().name();
#endif
}
