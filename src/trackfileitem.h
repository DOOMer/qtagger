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
