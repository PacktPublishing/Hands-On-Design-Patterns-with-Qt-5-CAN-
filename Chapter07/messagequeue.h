#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QObject>

class MessageQueue : public QObject
{
    Q_OBJECT
public:
    explicit MessageQueue(QObject *parent = nullptr);

    Q_INVOKABLE void send(const QString& message);

    Q_SIGNAL void messageReceived(const QString& message);
};

#endif // MESSAGEQUEUE_H
