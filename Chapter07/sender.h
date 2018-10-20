#pragma once
#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);

    Q_SIGNAL void newMessage(const QString& message);

    Q_INVOKABLE void sendMessage(const QString& message);
};
