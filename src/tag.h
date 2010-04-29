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
#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QTextCodec>
#include <QDebug>

#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "tagaudio.h"
#include "config.h"

struct TagData
{
    QString title;
    QString artist;
    QString album;
    quint16 year;
    quint8 tracknum;    
    QString genre;    
    QString comment;    
};

class Tag
{
public:
    Tag();
    Tag(const QString &file);
    virtual ~Tag();

    /**
     * Return audio properties
     *
     * @return Pointer to audio tag object
     */
    TagAudio *audio;

    /**
     * Reading tag data
     */
    virtual void readInfo();

    /**
     * Writing id3v2 tag data
     */
    virtual bool writeInfo();

    void setTitle(const QString &title);
    void setArtist(const QString &artist);
    void setAlbum(const QString &album);
    void setYear(const quint16 &year);
    void setTrackNum(const quint8 num);    
    void setGenre(const QString &genre);    
    void setComment(const QString &comment);
    void setFile(const QString &file);

    /**
     * convert data in tag for update track item info
     */
    void toUtfTag();

    /**
     * convert string to unicode
     *
     * @param String for convert
     * @return String converted to unicode
     */
    QString& toUtfTagStr(QString& str);

    /**
     * convert string to taglib string
     *
     * @param Sreing for convert
     * @return String converted to TagLib::String
     */
    TagLib::String toTagLibStr(QString str);

    QString& title() const;
    QString& artist() const;
    QString& album() const;
    quint16 year() const;
    quint8 trackNum() const;    
    QString& genre() const;
    QString& comment() const;
    QString file() const;    

private:
    TagData *data; /// tag data
    QString filename; /// filename of reading|writing tag data

    void Init(); /// initiale tag object
};

#endif // TAG_H
