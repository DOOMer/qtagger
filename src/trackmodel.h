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
#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QAbstractListModel>
#include <QtCore/QModelIndex>
#include <QtCore/QModelIndexList>
#include <QtCore/QList>
#include <QtGui/QColor>
#include <QtGui/QApplication>
#include <QtGui/QPalette>

#include "trackfileitem.h"

class TrackModel : public QAbstractListModel
{
Q_OBJECT
public:
    explicit TrackModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRow(int row, TrackFileItem *track);
    bool updateRow(const QModelIndex &index);
    bool removeRow(int row);    
    bool removeRows(QModelIndexList &rowsList);
    bool clear();
    TrackFileItem* getItem(int row);

    void setList(QList<TrackFileItem *> &list);
signals:

public slots:

private:
    QList<TrackFileItem *> *tracks;

};

#endif // TRACKMODEL_H
