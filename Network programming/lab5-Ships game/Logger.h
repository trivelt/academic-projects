#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QTextBrowser>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QTextBrowser* gameLogs, QTextBrowser* chat, QObject *parent = 0);
    
signals:
    
public slots:
    void logGameMessage(QString message);
    void logChatMessage(QString sender, QString message);
    
private:
    QString dateString();

    QTextBrowser* gameLogsBrowser;
    QTextBrowser* chatBrowser;
};

#endif // LOGGER_H
