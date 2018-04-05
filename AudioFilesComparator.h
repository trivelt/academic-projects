#ifndef AUDIOFILESCOMPARATOR_H
#define AUDIOFILESCOMPARATOR_H

#include <QString>

class AudioFilesComparator
{
public:
    AudioFilesComparator();
    double compareTwoFiles(QString filepath1, QString filepath2);
    bool isTheSameVoice(double correlation);
    QString recognizeVoice(QString filepath);
    static int counter;

};

#endif // AUDIOFILESCOMPARATOR_H
