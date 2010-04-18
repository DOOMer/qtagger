#include "tag.h"

Tag::Tag()
{
    data = new TagData;
    if (data)
    {
        Init();
        audio = new TagAudio();
    }
}

Tag::Tag(const QString &file)
    :filename(file)
{
    data = new TagData;
    if (data)
    {
        Init();
        audio = new TagAudio(filename);
    }
}

Tag::~Tag()
{
    delete audio;
    delete data;
}


void Tag::Init()
{
    data->title = "";
    data->artist = "";
    data->album = "";
    data->year = 0;
    data->tracknum = 0;    
    data->genre = "";    
    data->comment = "";    
}

void Tag::setFile(const QString &file)
{
    filename = file;
    audio->setFile(filename);
    readInfo();
}

QString Tag::file() const
{
    return filename;
}

TagLib::String Tag::toTagLibStr(QString str)
{
    TagLib::String taglibStr(str.toUtf8().data(), TagLib::String::UTF8);
    if (taglibStr.isLatin1() == true)
    {
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QByteArray arr;
        arr.append(str);
        str = codec->toUnicode(arr);
        return TagLib::String(str.toUtf8().data(), TagLib::String::UTF8);
    }
    else
    {
        return taglibStr;
    }
}

// readi tag info from file
void Tag::readInfo()
{
    qDebug() << "file == " << filename;

    TagLib::FileRef ref(filename.toLocal8Bit());

    // if fileref is not null
    if (ref.isNull() == false && ref.tag())
    {
        TagLib::Tag *fileTag = ref.tag();

        setTitle(QString::fromUtf8(fileTag->title().toCString(true)));
        setArtist(QString::fromUtf8(fileTag->artist().toCString(true)));
//        setArtist(TStringToQString(fileTag->artist()));
        setAlbum(QString::fromUtf8(fileTag->album().toCString(true)));
        setYear(fileTag->year());
        setGenre(QString::fromUtf8(fileTag->genre().toCString(true)) );

        setTrackNum(fileTag->track());
//        setDiskNum(fileTag->d);
        setComment(QString::fromUtf8(fileTag->comment().toCString(true)));

    }
    qDebug() << "audio ptr === " << audio;
//    if (audio)
//    {
//        qDebug() << "------------ valid" ;
//    }
    audio->readAuidioInfo();

}


// write tag info to file
bool Tag::writeInfo()
{
    qDebug() << "file == " << filename;
    qDebug() << "file == " << filename;

    TagLib::FileRef ref(filename.toLocal8Bit());

    if (ref.isNull() == false && ref.tag())
    {
        TagLib::Tag *fileTag = ref.tag();

        fileTag->setTitle(toTagLibStr(title()));
        fileTag->setAlbum(toTagLibStr(album()));
        fileTag->setArtist(toTagLibStr(artist()));
        fileTag->setComment(toTagLibStr(comment()));
        fileTag->setGenre(toTagLibStr(genre()));
        fileTag->setYear(year());
        fileTag->setTrack(trackNum());

        return ref.save();
    }
    else
    {
        qDebug() << "not tagged";
        return false;
    }
}

// setters

void Tag::setTitle(const QString &title)
{
    data->title = title;
}

QString Tag::title() const
{
    return data->title;
}

void Tag::setArtist(const QString &artist)
{
    data->artist = artist;
}

QString Tag::artist() const
{
    return data->artist;
}


void Tag::setAlbum(const QString &album)
{
    data->album = album;
}

QString Tag::album() const
{
    return data->album;
}

// ---- Year info

void Tag::setYear(const quint16 &year)
{
    data->year = year;
}

quint16 Tag::year() const
{
    return data->year;
}

// --- trackNum info

void Tag::setTrackNum(quint8 num)
{
        data->tracknum = num;
}

quint8 Tag::trackNum() const
{
    return data->tracknum;
}

// --- genre info

void Tag::setGenre(const QString &genre)
{
    data->genre = genre;
}

QString Tag::genre() const
{
    return data->genre;
}

// --- comment info

void Tag::setComment(const QString &comment)
{
    data->comment = comment;
}

QString Tag::comment() const
{
    return data->comment;
}
