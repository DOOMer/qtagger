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
#include "qtagger.h"

QTagger::QTagger(QObject *parent) :
    QObject(parent), conf(Config::instance())
{
    model = new TrackModel;
    model->setList(tracks);
    current = new Tag;
    _lastAddedDir = QDir::homePath();
}

QTagger::~QTagger()
{    
    delete current;
    delete model;
    qDebug() << "Destruced app";
    conf->killInstance();
}

TrackModel* QTagger::getTrackModel()
{
    return model;
}

void QTagger::createTrackItem(const QString &file)
{
    TrackFileItem *track = new TrackFileItem(file, current);
    model->insertRow(model->rowCount(), track);
}

void QTagger::addFiles(QStringList &files)
{
    QStringList::const_iterator icurrent;
    for (icurrent = files.constBegin(); icurrent != files.constEnd(); ++icurrent)
    {
        createTrackItem((*icurrent));
    }
}

void QTagger::iterateDir(QDir &selectDir)
{
    _lastAddedDir = selectDir.path();
    QDirIterator it(selectDir.path(),QDir::Dirs|QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        selectDir.setPath(it.next());
        addDir(selectDir);
        qApp->processEvents();
    }
}

void QTagger::addDir(QDir &selectDir)
{
    QStringList fileFilters;
    fileFilters << "*.mp3";

    selectDir.setNameFilters(fileFilters);

    QStringList fileNames = selectDir.entryList();

    if (fileNames.isEmpty() != true)
    {
        QStringList::iterator icurrent;
        for (icurrent = fileNames.begin(); icurrent != fileNames.end(); ++icurrent)
        {
            (*icurrent).prepend(selectDir.path() + QDir::separator() );
            createTrackItem((*icurrent));
        }
    }    
}

void QTagger::removeFiles(QModelIndexList &indexez)
{
    model->removeRows(indexez);
}

bool QTagger::updateItem(QModelIndex &index)
{
    TrackFileItem *selectTrack = model->getItem(index.row());

    selectTrack->setData(TRACK_INFO_TITLE, current->title());
    selectTrack->setData(TRACK_INFO_ALBUM, current->album());
    selectTrack->setData(TRACK_INFO_ARTIST, current->artist());

    return model->updateRow(index);
}

void QTagger::clearList()
{
    model->clear();    
}

bool QTagger::toUnicode(QModelIndexList &indexez)
{

    qDebug() << indexez.isEmpty();
    if (indexez.isEmpty() == false)
    {
        qSort(indexez.begin(), indexez.end());

        QModelIndexList::iterator icurrent;
        for (icurrent = indexez.begin(); icurrent != indexez.end(); ++icurrent)
        {
            current->setFile(model->getItem((*icurrent).row())->getFile());
            current->toUtfTag();
            updateItem((*icurrent));
        }
        return true;
    }
    else
    {
        return false;
    }
}

void QTagger::setTag(Tag *tag)
{
    current = tag;
}

Tag* QTagger::currentTag()
{
    return current;
}

Config* QTagger::config()
{
    return Config::instance();
}

QString& QTagger::lastAddedDir()
{
    QString& retDir = _lastAddedDir;
    return retDir;
}
