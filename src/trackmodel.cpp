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

    // FIXME -- makenormal headers
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
//        str = "Column " + QString::number(section + 1);
    }

    return QVariant( str);
}

QVariant TrackModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << "index " << index.isValid();

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


        return QVariant(tracks->at(index.row())->data(index.column())); //->getFile());
        break;
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
//    tracks.insert(row, track);
    tracks->append(track);
    endInsertRows();
    return true;
}

bool TrackModel::removeRow(int row)
{
    if (row != -1)
    {
        beginRemoveRows(QModelIndex(), row, row);
        TrackFileItem *track = tracks->takeAt(row);
        delete track;

        qDebug() << "rows after removed " << tracks->count();
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
