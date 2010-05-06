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

#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include "tag.h"


const QString TRACK_INFO_TITLE = "title";
const QString TRACK_INFO_ARTIST = "artist";
const QString TRACK_INFO_ALBUM = "album";
const QString TRACK_INFO_TIME = "time";

class TrackFileItem
{
public:
    /**
     * convert string to unicode
     *
     * @param Sreing for filename
     * @param tag pointer
     */
    TrackFileItem(const QString &file, Tag *tag);    

    /**
     * Create empty traclist item
     */
    TrackFileItem();

    /**
     * Return current trackitem
     *
     * @return pointer on this trackitem object
     */
    TrackFileItem* self();

    /**
     * Return filename of trackitem
     *
     * @return  String filename
     */
    QString getFile() const;

    /**
     * Get number of trackdata items
     *
     * @return integer fo nymbers trackdata items
     */
    int columnCount() const;

    /**
     * Return data value
     *
     * @param int num of selected colum
     * @return Variant data
     */
    QVariant data(int colum) const;

    void setData(const QString key, const QString &value);

    /**
     * Return data value (overloaded)
     *
     * @param Sreing key
     * @return Variant data
     */
    QVariant data(const QString &key) const;

private:
    QString fileName;
    QMap<QString, QVariant> trackData;    
};

#endif // TRACKFILEITEM_H
