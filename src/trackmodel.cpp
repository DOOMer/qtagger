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
#include "trackmodel.h"

TrackModel::TrackModel(QObject *parent) :
    QAbstractListModel(parent), tracks(new QList<TrackFileItem *>)
{

}

int TrackModel::rowCount(const QModelIndex &parent) const
{
    return tracks->count();
}

int TrackModel::columnCount(const QModelIndex &parent) const
{
    return 4; // TODO -- make normal dynamic count
}

QVariant TrackModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    QString str;

    if (orientation != Qt::Vertical)
    {
        switch (section)
        {
        case 0:
            str = tr("Title"); break;
        case 1:
            str = tr("Artist"); break;
        case 2:
            str = tr("Album"); break;
        case 3:
            str = tr("Time"); break;
        default:
            break;
        }
    }

    return QVariant(str);
}

QVariant TrackModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return QVariant(tracks->at(index.row())->data(TRACK_INFO_TITLE));
        case 1:
            return QVariant(tracks->at(index.row())->data(TRACK_INFO_ARTIST));
        case 2:
            return QVariant(tracks->at(index.row())->data(TRACK_INFO_ALBUM));
        case 3:
            return QVariant(tracks->at(index.row())->data(TRACK_INFO_TIME));
        default:
            break;
        }
        break;        
    case Qt::BackgroundColorRole:
        {
            int batch = index.row() % 2;
            if (batch == 0)
                return qApp->palette().base();
            else
                return qApp->palette().alternateBase();
            break;
        }
    case Qt::ToolTipRole:
        return QVariant(tracks->at(index.row())->getFile());
        break;
    default:
        return QVariant();
    }
}


bool TrackModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}

Qt::ItemFlags TrackModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


bool TrackModel::insertRow(int row, TrackFileItem *track)
{
    if (row == -1)
    {
        row = rowCount();
    }

    beginInsertRows(QModelIndex(), row, row);

    tracks->append(track);
    endInsertRows();
    return true;
}

bool TrackModel::updateRow(const QModelIndex &index)
{    
    int row = index.row();
    if (row == -1)
    {
        qDebug() << "row is " << row;
        return false;
    }
    else
    {
        dataChanged(index, index);
        return true;
    }
}

bool TrackModel::removeRow(int row)
{
    if (row != -1)
    {
        beginRemoveRows(QModelIndex(), row, row);
        TrackFileItem *track = tracks->takeAt(row);
        delete track;

        endRemoveRows();
        return true;
    }
    else
    {
        return false;
    }
}

bool TrackModel::removeRows(QModelIndexList &rowsList)
{
    qSort(rowsList.begin(), rowsList.end(), qGreater<QModelIndex>());

    QModelIndexList::const_iterator icurrent;
    for (icurrent = rowsList.constBegin(); icurrent != rowsList.constEnd(); ++icurrent)
    {
        removeRow((*icurrent).row());
    }
    return true;
}

bool TrackModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, tracks->count() -1);
    qDeleteAll(*tracks);
    tracks->clear();
    endRemoveRows();
    return true;
}

TrackFileItem* TrackModel::getItem(int row)
{
    return tracks->at(row);
}

void TrackModel::setList(QList<TrackFileItem *> &list)
{
    tracks = &list;
}
