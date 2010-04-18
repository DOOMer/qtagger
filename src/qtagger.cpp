#include "qtagger.h"

QTagger::QTagger(QObject *parent) :
    QObject(parent)
{
    model = new TrackModel;
    model->setList(tracks);
    current = new Tag;
}

QTagger::~QTagger()
{
    delete current;
    delete model;    
}

TrackModel* QTagger::getTrackModel()
{
    return model;
}

void QTagger::createTrackItem(const QString &file)
{
    TrackFileItem *track = new TrackFileItem(file, current);
    model->insertRow(model->rowCount(), track);
    qDebug() << "tracks.size() " << tracks.size();
}

void QTagger::addFiles(QStringList &files)
{
    QStringList::const_iterator icurrent;
    for (icurrent = files.constBegin(); icurrent != files.constEnd(); ++icurrent)
    {
        createTrackItem((*icurrent));
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
    qDebug() << __PRETTY_FUNCTION__ << "debug qlist" << tracks.size();
}

void QTagger::clearList()
{
    model->clear();
    qDebug() << "debug qlist" << tracks;
}

bool QTagger::toUnicode()
{    
//    QTextCodec *pCodec = QTextCodec::codecForName("Windows-1251");
//    QByteArray arr;
//    arr.append(currentTag()->title());
//    currentTag()->setTitle(pCodec->toUnicode(arr));
//    qDebug() << "currentTag()->title()   " << currentTag()->title();

    // TODO -- зафигачить байт-масси в отдельную функцию, передавать ей строку и выкидывать юникодный кустринг, отдаваемый  таг-классу

    return true;
}

void QTagger::setTag(Tag *tag)
{
    qDebug() << "setting tag " << tag;
    current = tag;
}

Tag* QTagger::currentTag()
{
    return current;
}
