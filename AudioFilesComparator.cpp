#include "AudioFilesComparator.h"
#include "Recording.h"
#include "XmlDatabaseReader.h"
#include "VoiceRecognizer.h"
#include <QHash>
#include <QDebug>

int AudioFilesComparator::counter = 0;

AudioFilesComparator::AudioFilesComparator()
{

}

double AudioFilesComparator::compareTwoFiles(QString filepath1, QString filepath2)
{
//    qDebug() << "Called counter for " << filepath1 << " and " << filepath2;
    counter++;
//    if(counter == 1)
//        return 0.2;
//    if(counter == 2)
//        return 0.03;
//    if(counter == 3)
//        return 0.34;
    return VoiceRecognizer::getCorrCoefficientBetweenTwoSamples(filepath1.toStdString(), filepath2.toStdString());
}

bool AudioFilesComparator::isTheSameVoice(double correlation)
{
    return correlation > 0.2;
}

QString AudioFilesComparator::recognizeVoice(QString filepath)
{
    QList<Recording> recordings = XmlDatabaseReader::getRecordings();
    QHash<QString, QList<double>* > correlations;

    if(recordings.isEmpty())
    {
        return "No correlations found (empty database?)";
    }

    foreach (Recording recording, recordings)
    {
        QString author = recording.getAuthor();
        double correlation = compareTwoFiles(filepath, recording.getFilepath());
        if(correlations.contains(author))
        {
            correlations.value(author)->append(correlation);
        }
        else
        {
            QList<double>* list = new QList<double>;
            list->append(correlation);
            correlations[author] = list;
        }
    }

    QString bestAuthor = "";
    double bestAvgCorrelation = 0;

    QHash<QString, double> avgCorrelations;
    foreach (QString author, correlations.keys())
    {
        QList<double>* authorCorrelations = correlations.value(author);
        double sum = 0;
        for(int i=0; i<authorCorrelations->size(); i++)
        {
            sum += authorCorrelations->at(i);
        }
        double avgCorrelation = sum / authorCorrelations->size();
        avgCorrelations[author] = avgCorrelation;

        if(avgCorrelation > bestAvgCorrelation)
        {
            bestAuthor = author;
            bestAvgCorrelation = avgCorrelation;
        }
        else if(avgCorrelation == bestAvgCorrelation)
        {
            bestAuthor = "";
        }
    }

    QString resultText = "";
    if(bestAuthor != "")
    {
        resultText += "<b>This voice was recognized as the voice of " + bestAuthor;
        resultText += " (avg correlation " + QString::number(bestAvgCorrelation) + ")</b><br /><br />";
    }

    foreach(QString author, avgCorrelations.keys())
    {
        resultText += author + " (" + QString::number(avgCorrelations.value(author)) + ")<br />";
    }

    return resultText;
}
