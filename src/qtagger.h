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
