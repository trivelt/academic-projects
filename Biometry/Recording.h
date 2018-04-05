#ifndef RECORDING_H
#define RECORDING_H

#include <QString>

class Recording
{
public:
    Recording(QString title, QString filepath, QString author, QString date);
    inline QString getTitle() const {return title;}
    inline QString getFilepath() const {return filepath;}
    inline QString getAuthor() const {return author;}
    inline QString getDate() const {return date;}

private:
    QString title;
    QString filepath;
    QString author;
    QString date;
};

#endif // RECORDING_H
