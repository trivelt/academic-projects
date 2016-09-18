#include "Logger.h"
#include <QDebug>
#include <QTime>

Logger::Logger(QTextBrowser *gameLogs, QTextBrowser *chat, QObject *parent) :
    QObject(parent),
    gameLogsBrowser(gameLogs),
    chatBrowser(chat)
{
}

void Logger::logChatMessage(QString sender, QString message)
{
    message = message.trimmed();
    QString messageToAppend = "<strong>";
    messageToAppend += sender;
    messageToAppend += "</strong>: ";
    messageToAppend += message;
    chatBrowser->append(messageToAppend);
}


void Logger::logGameMessage(QString message)
{
    QString messageToAppend = dateString();
    messageToAppend += message;
    gameLogsBrowser->append(messageToAppend);
}

QString Logger::dateString()
{
    QTime time = QTime::currentTime();
    QString timeString = "[";
    timeString += time.toString();
    timeString += "] ";
    return timeString;
}
