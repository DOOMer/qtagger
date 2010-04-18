#ifndef TRACKFILEITEM_H
#define TRACKFILEITEM_H

#include <QString>
#include <QDebug>
#include <QHash>
#include <QMap>
#include <QVariant>

#include "tag.h"


const QString TRACK_INFO_TITLE = "title";
const QString TRACK_INFO_ARTIST = "artist";
const QString TRACK_INFO_ALBUM = "album";
const QString TRACK_INFO_TIME = "time";

class TrackFileItem
{
public:
    TrackFileItem(const QString &file, Tag *tag);    
    TrackFileItem();
    TrackFileItem* self();
    QString getFile() const;

    int columnCount() const;
    QVariant data(int colum) const;
    void setData(const QString key, const QString &value);
    QVariant data(const QString &key) const;

private:
    QString fileName;
    QMap<QString, QVariant> trackData;
};

#endif // TRACKFILEITEM_H
