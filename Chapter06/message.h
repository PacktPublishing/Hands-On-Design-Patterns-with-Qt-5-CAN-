#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString content READ content WRITE setContent)

public:
    Message() = default;
    Message(int id, const QString& type, const QString& content);

    int id() const;
    void setId(int id);

    QString type() const;
    void setType(const QString &type);

    QString content() const;
    void setContent(const QString &content);

private:
    int m_id;
    QString m_type;
    QString m_content;
};

#endif // MESSAGE_H
