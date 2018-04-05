#ifndef XMLDATABASEWRITER_H
#define XMLDATABASEWRITER_H
#include "Recording.h"

class XmlDatabaseWriter
{
public:
    XmlDatabaseWriter();
    static bool addRecordingToDatabase(Recording newRecording);
};

#endif // XMLDATABASEWRITER_H
