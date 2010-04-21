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

bool TrackFileItem::isNoUtf() const
{
    return latin1;
}

void TrackFileItem::setNoUtf(bool val)
{
    latin1 = val;
}
