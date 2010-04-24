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
#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QHash>
#include <QVariant>
#include <QDir>
#include <QFile>
#include <QDebug>

// default values
const QString DEFAULT_ENCODING = "ISO-8859-1";
const quint8 DEFAULT_TOOLBAR_TYPE = 0;

// key constants
const QString KEY_SOURCE_ENCODING = "soueceEncodeing";
const QString KEY_TOOLBAR_DYSPLAY = "toolbarType";

namespace CfgFlags
{
    enum ToolbarType
    {
        tbTextIcon = 0,
        tbIcon = 1,
        tbText =2
    };

};

class Config
{
public:
    static Config* instance();
    static void killInstance();
    static QString getSysLang();

    void loadSettings();
    void saveSettings();
    void defaultSettings();

    QVariant value(const QString &key);
    void setValue(const QString& key, QVariant val);

private:
    Config();
    Config(const Config &);
    Config& operator=(const Config& );

    static QString configFile();

    static Config *ptrInstance;
    QHash<QString, QVariant> confData;
};

#endif // CONFIG_H
