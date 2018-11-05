#include "messagequeue.h"

MessageQueue::MessageQueue(QObject *parent) : QObject(parent)
{

}

void MessageQueue::send(const QString &message)
{
    emit messageReceived(message);
}
