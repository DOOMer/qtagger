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
