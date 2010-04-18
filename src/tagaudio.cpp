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
#include "tagaudio.h"

TagAudio::TagAudio()
{
    data = new TagDataAudio;
    if (data)
    {
        Init();
////        readAuidioInfo();
//        qDebug() << "bitrate " << data->bitrate;
    }
}

// not worked
TagAudio::TagAudio(QString &file)
    :filename(file)
{
    data = new TagDataAudio;
    if (data)
    {
        Init();
//        readAuidioInfo();
//        qDebug() << "bitrate " << data->bitrate;
    }
}

void TagAudio::Init()
{
    data->length = 0;
    data->rate = 0;
    data->bitrate = 0;
}

TagAudio* TagAudio::audio()
{
    return this;
}

void TagAudio::setFile(QString &file)
{
    filename = file;
}

void TagAudio::readAuidioInfo()
{
    qDebug() << "entering read audio info ...." << filename.toLocal8Bit();
    TagLib::FileRef ref(filename.toLocal8Bit());

    if (ref.isNull() == false && ref.audioProperties())
    {
        TagLib::AudioProperties *properties = ref.audioProperties();
        data->length = properties->length();
        data->rate = properties->sampleRate();
        data->bitrate = properties->bitrate();
    }
    qDebug() << "exiting read audio info ....";
}

uint TagAudio::bitrate() const
{
    return data->bitrate;
}

uint TagAudio::sampleRate() const
{
    return data->rate;
}

QString TagAudio::timeStr()
{
    uint sec = data->length % 60;
    uint min = (data->length - sec) / 60;

    return QString::number(min) + ":" + QString::number(sec);
}
