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
        qDebug() << "no ptr";
        ptrInstance = new Config;
    }
    else
    {
        qDebug() << "ptr existinmg";
    }
    return ptrInstance;
}

void Config::killInstance()
{
    if (ptrInstance)
    {
        qDebug() << "killing..... ";
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
    qDebug() << "load settings";

    // check existing file
    if (QFile::exists(Config::configFile()) == false)
    {
        defaultSettings();
    }
    else
    {
        QSettings loader(Config::configFile().toAscii(), QSettings::IniFormat);
        qDebug() << "_prepare()" << loader.fileName();

        loader.beginGroup("Main");
        confData.insert(KEY_SOURCE_ENCODING, loader.value(KEY_SOURCE_ENCODING, DEFAULT_ENCODING).toString());
        loader.endArray();
        loader.beginGroup("Display");
        confData.insert(KEY_TOOLBAR_DYSPLAY, loader.value(KEY_TOOLBAR_DYSPLAY, DEFAULT_TOOLBAR_TYPE));
        loader.endArray();
        qDebug() << "=== " << confData;
    }
}

void Config::saveSettings()
{
    qDebug() << "save settings";
    QSettings saver(Config::configFile().toAscii(), QSettings::IniFormat);

    // write settings
    saver.beginGroup("Main");
    saver.setValue(KEY_SOURCE_ENCODING, QVariant(DEFAULT_ENCODING).toString());
    saver.endArray();

    saver.beginGroup("Display");
    saver.setValue(KEY_TOOLBAR_DYSPLAY, QVariant(DEFAULT_TOOLBAR_TYPE).toUInt());
    saver.endArray();
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
