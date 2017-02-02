#include "XmlDatabaseWriter.h"
#include "XmlDatabaseReader.h"
#include "InitParameters.h"
#include "QFile"
#include <QTextStream>
#include <QDebug>

XmlDatabaseWriter::XmlDatabaseWriter()
{

}

bool XmlDatabaseWriter::addRecordingToDatabase(Recording newRecording)
{
    QString xmlString = "<xml>\n<recordings>\n";
    QList<Recording> recordings = XmlDatabaseReader::getRecordings();
    recordings.append(newRecording);
    foreach (Recording recording, recordings)
    {
        xmlString += "\t<recording>\n";
        xmlString += "\t\t<title>" + recording.getTitle() + "</title>\n";
        xmlString += "\t\t<filepath>" + recording.getFilepath() + "</filepath>\n";
        xmlString += "\t\t<author>" + recording.getAuthor() + "</author>\n";
        xmlString += "\t\t<date>" + recording.getDate() + "</date>\n";
        xmlString += "\t</recording>\n";
    }
    xmlString += "</recordings>\n</xml>";

    QFile outputFile(InitParameters::configFilepath());
    if (outputFile.open(QIODevice::WriteOnly)) {
        QTextStream outstream(&outputFile);
        outstream << xmlString;
    }
    outputFile.close();

    return true;
}
