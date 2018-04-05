#include "XmlDatabaseReader.h"
#include "InitParameters.h"

#include <QFile>
#include <QDebug>
#include <QDomDocument>

XmlDatabaseReader::XmlDatabaseReader()
{

}

QList<Recording> XmlDatabaseReader::getRecordings()
{
    QDomDocument xmlConfigDoc("xmlConfig");
    QList<Recording> recordings;
    QString filename = InitParameters::configFilepath();
    QFile configFile(filename);
    if(!configFile.open(QIODevice::ReadOnly))
    {
        qCritical() << "XmlDatabaseReader could not open config file " << filename;
        return recordings;
    }
    if (!xmlConfigDoc.setContent(&configFile)) {
        qCritical() << "XmlDatabaseReader could not parse XML config file " << filename;
        configFile.close();
        return recordings;
    }

    QDomElement docElem = xmlConfigDoc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if(e.tagName() == "recordings")
            {
                QDomNode recordingNode = e.firstChildElement();
                while(!recordingNode.isNull())
                {
                    QDomElement recordingElement = recordingNode.toElement();

                    QDomElement titleElement = recordingElement.elementsByTagName("title").at(0).toElement();
                    QDomElement filepathElement = recordingElement.elementsByTagName("filepath").at(0).toElement();
                    QDomElement authorElement = recordingElement.elementsByTagName("author").at(0).toElement();
                    QDomElement dateElement = recordingElement.elementsByTagName("date").at(0).toElement();
                    Recording recording(titleElement.text(), filepathElement.text(), authorElement.text(), dateElement.text());
                    recordings.append(recording);

                    recordingNode = recordingNode.nextSibling();
                }
            }
        }
        n = n.nextSibling();
    }
   configFile.close();
   return recordings;
}
