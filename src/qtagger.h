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

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>

#include "config.h"
#include "tag.h"
#include "trackmodel.h"
#include "trackfileitem.h"

class QTagger : public QObject
{
    Q_OBJECT
public:
    explicit QTagger(QObject *parent = 0);
    ~QTagger();

    /**
     * Return pointer on trackmodel object
     *
     * @param trackModel pounter
     */
    TrackModel* getTrackModel();

    /**
     * Create trackmodel item
     *
     * @param String path to open file
     */
    void createTrackItem(const QString &file);

    /**
     * Added some files to list
     *
     * @param list of added filenames
     */
    void addFiles(QStringList &files);

    /**
     * Added dir with all contains file
     *
     * @param path to added dir
     */
    void addDir(QDir &selectDir);

    /**
     * Iterate subdirs frim adding dir
     *
     * @param Selected dir
     */
    void iterateDir(QDir &selectDir);

    /**
     * Remove selected files
     *
     * @param Modelindexes with selected items
     */
    void removeFiles(QModelIndexList &indexez);

    /**
     * Update current item data
     *
     * @param Modelindex of current item
     */
    bool updateItem(QModelIndex &index);

    /**
     * Clear list (delete all items)
     */
    void clearList();

    /**
     * Convert to Utf selected items
     *
     * @param Modelindexes with selected items
     */
    bool toUnicode(QModelIndexList &indexez);

    /**
     * Return pointer on trackmodel object
     *
     * @param trackModel pounter
     */
    void setTag(Tag *tag);

    /**
     * Return current item tag
     *
     * @return Pointer to current item  tag
     */
    Tag* currentTag();

    /**
     * Return config object
     *
     * @return Pointer to config object
     */
    Config* config();

    /**
     * Return last added dir
     *
     * @return String path to last added dir
     */
    QString& lastAddedDir();
signals:

protected:
    Config *conf;

public slots:

private:
    QList<TrackFileItem *> tracks;
    TrackModel *model;
    Tag *current;
    QString _lastAddedDir;
};

#endif // QTAGGER_H
