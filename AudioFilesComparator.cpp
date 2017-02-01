#include "AudioFilesComparator.h"

AudioFilesComparator::AudioFilesComparator()
{

}

double AudioFilesComparator::compareTwoFiles(QString filepath1, QString filepath2)
{
    return 0.2;
}

bool AudioFilesComparator::isTheSameVoice(double correlation)
{
    return correlation > 0.2;
}
