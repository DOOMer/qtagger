#include "trackfileitem.h"

TrackFileItem::TrackFileItem(const QString &file, Tag *tag)
    :fileName(file) // fileTag(tag),
{
    tag->setFile(file);
    tag->readInfo();

    trackData.insert(TRACK_INFO_TITLE, QVariant(tag->title()));
    trackData.insert(TRACK_INFO_ARTIST, QVariant(tag->artist()));
    trackData.insert(TRACK_INFO_ALBUM, QVariant(tag->album()));
    trackData.insert(TRACK_INFO_TIME, QVariant(tag->audio->timeStr()));
}

TrackFileItem::TrackFileItem()
{

}

TrackFileItem* TrackFileItem::self()
{
    return this;
}

QString TrackFileItem::getFile() const
{
    return fileName;
}

int TrackFileItem::columnCount() const
{
    return trackData.count();
}

QVariant TrackFileItem::data(int colum) const
{
    if (colum > trackData.count() - 1)
    {
        colum = trackData.count() - 1;
    }

    QList<QString> keys = trackData.keys();

//        qDebug() << "keys___ ---" << trackData.keys() ;
//        qDebug() << "values__ ---" << trackData.values();

    return trackData.value(keys.value(colum));
}

QVariant TrackFileItem::data(const QString &key) const
{
    return trackData.value(key);
}

void TrackFileItem::setData(QString key, const QString &value)
{
    trackData.insert(key, value);
}
