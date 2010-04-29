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
#ifndef TAGAUDIO_H
#define TAGAUDIO_H

#include <QString>
#include <QDebug>

#include <taglib/fileref.h>
#include <taglib/tag.h>
//#include "tag.h";

struct TagDataAudio
{
    uint length;
    uint rate;
    uint bitrate;
};

class TagAudio
{
public:
    TagAudio();
    TagAudio(QString &file);
    TagAudio* audio();
    void setFile(QString &file);
    void readAuidioInfo();
    uint bitrate() const;
    uint sampleRate() const;
    QString timeStr();

private:
    void Init();    
    TagDataAudio *data;
    QString filename;
};

#endif // TAGAUDIO_H
