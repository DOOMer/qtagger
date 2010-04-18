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
#ifndef QTAGGER_H
#define QTAGGER_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QDir>
//#include <QTextCodec>
#include <QDebug>

#include "tag.h"
#include "trackmodel.h"
#include "trackfileitem.h"

class QTagger : public QObject
{
    Q_OBJECT
public:
    explicit QTagger(QObject *parent = 0);
    ~QTagger();

    TrackModel* getTrackModel();
    void createTrackItem(const QString &file);
    void addFiles(QStringList &files);
    void addDir(QDir &selectDir);
    void removeFiles(QModelIndexList &indexez);
    void clearList();
    bool toUnicode();
    void setTag(Tag *tag);
    Tag* currentTag();
signals:

public slots:

private:
    QList<TrackFileItem *> tracks;
    TrackModel *model;
    Tag *current;
};

#endif // QTAGGER_H
