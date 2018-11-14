#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

QStringList Logger::messages() const
{
    return m_messages;
}

void Logger::setMessages(const QStringList &messages)
{
    m_messages = messages;
}

void Logger::log(const QString &message)
{
    m_messages << message;
    emit messagesChanged();
}
