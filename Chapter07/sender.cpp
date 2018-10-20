#include "sender.h"

Sender::Sender(QObject *parent) : QObject(parent)
{
}

void Sender::sendMessage(const QString& message) {
    emit newMessage(message);
}
