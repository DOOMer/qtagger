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

#include <QtCore/QSettings>
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QtGlobal>
#include <QtCore/QLocale>

// default values
const QString DEFAULT_ENCODING = "windows-1250";
const quint8 DEFAULT_TOOLBAR_TYPE = 1;

// key constants
const QString KEY_SOURCE_ENCODING = "soueceEncodeing";
const QString KEY_TOOLBAR_DYSPLAY = "toolbarType";

namespace CfgFlags
{
    /**
     * @enum Enum for toolbar types
     */
    enum ToolbarType
    {
        tbTextIcon = 0, /// toolbottons with text & icons
        tbIcon = 1, /// toolbottons with only icons
        tbText = 2  /// toolbottons with only text
    };
};

/**
 * @class Class provides storage for configuration data and works with it
 */
class Config
{
public:
    /**
     * Get current instance of configuration object
     * @return Pointer on created object
     */
    static Config* instance();

    /**
     * Destroy current Config object
     */
    static void killInstance();

    /**
     * Get system language
     * @return String with current system locale
     */
    static QString getSysLang();

    /**
     * Load configuration data from conf file
     */
    void loadSettings();

    /**
     * Save configuration data to conf file
     */
    void saveSettings();

    /**
     * Reset configuration data from default values
     */
    void defaultSettings();

    /**
     * Return value on configuration parameter
     *
     * @param String of name key
     * @return QVariant value of configuration parameter
     */
    QVariant value(const QString &key);

    /**
     * Set value on configuration parameter
     *
     * @param String of name key
     * @param String of saved value
     */
    void setValue(const QString& key, QVariant val);

private:
    Config();
    Config(const Config &);
    Config& operator=(const Config& );

    /**
     * Return path to configuration file
     *
     * @return String path to conf file
     */
    static QString configFile();

    static Config *ptrInstance;
    QHash<QString, QVariant> confData;
};

#endif // CONFIG_H
