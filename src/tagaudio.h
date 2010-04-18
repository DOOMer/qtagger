#ifndef TAGAUDIO_H
#define TAGAUDIO_H

#include <QString>
#include <QDebug>

#include <taglib/fileref.h>
#include <taglib/tag.h>
//#include "tag.h";

struct TagDataAudio
{
    uint length;
    uint rate;
    uint bitrate;
};

class TagAudio
{
public:
    TagAudio();
    TagAudio(QString &file);
    TagAudio* audio();
    void setFile(QString &file);
    void readAuidioInfo();
    uint bitrate() const;
    uint sampleRate() const;
    QString timeStr();

private:
    void Init();    
    TagDataAudio *data;
    QString filename;
};

#endif // TAGAUDIO_H
