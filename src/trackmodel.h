#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QModelIndexList>
#include <QList>

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
