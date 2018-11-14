#include "message.h"

Message::Message(int id, const QString &type, const QString &content)
    : m_id(id), m_type(type), m_content(content)
{

}

int Message::id() const
{
    return m_id;
}

void Message::setId(int id)
{
    m_id = id;
}

QString Message::type() const
{
    return m_type;
}

void Message::setType(const QString &type)
{
    m_type = type;
}

QString Message::content() const
{
    return m_content;
}

void Message::setContent(const QString &content)
{
    m_content = content;
}
