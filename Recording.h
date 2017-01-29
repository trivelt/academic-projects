#ifndef RECORDING_H
#define RECORDING_H

#include <QString>

class Recording
{
public:
    Recording();

private:
    QString author;
    QString filepath;
    QString filename;
    QString description;
    QString date;
};

#endif // RECORDING_H
