#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messages READ messages WRITE setMessages NOTIFY messagesChanged)

public:
    explicit Logger(QObject *parent = nullptr);

    QStringList messages() const;

    void setMessages(const QStringList &messages);

    Q_INVOKABLE void log(const QString &message);

signals:
    void messagesChanged();

private:
    QStringList m_messages;
};

#endif // LOGGER_H
