#ifndef XMLDATABASEREADER_H
#define XMLDATABASEREADER_H

#include "Recording.h"
#include <QList>

class XmlDatabaseReader
{
public:
    XmlDatabaseReader();
    static QList<Recording> getRecordings();
};

#endif // XMLDATABASEREADER_H
