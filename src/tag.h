#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QTextCodec>
#include <QDebug>

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "tagaudio.h"

struct TagData
{
    QString title;
    QString artist;
    QString album;
    quint16 year;
    quint8 tracknum;    
    QString genre;    
    QString comment;    
};

class Tag
{
public:
    Tag();
    Tag(const QString &file);
    ~Tag();

    TagAudio *audio;
    void readInfo();    
    bool writeInfo();

    void setTitle(const QString &title);
    void setArtist(const QString &artist);
    void setAlbum(const QString &album);
    void setYear(const quint16 &year);
    void setTrackNum(const quint8 num);    
    void setGenre(const QString &genre);    
    void setComment(const QString &comment);
    void setFile(const QString &file);

    TagLib::String toTagLibStr(QString str);

    QString title() const ;
    QString artist() const;
    QString album() const;
    quint16 year() const;
    quint8 trackNum() const;    
    QString genre() const;
    QString comment() const;    
    QString file() const;    

private:
    TagData *data;
    QString filename;

    void Init();    
};

#endif // TAG_H
