#include <QCoreApplication>
#include <QtCore>
#include <gtest/gtest.h>
#include "messagequeue.h"
#include "logger.h"
#include "message.h"

template <typename T>
struct has_squeeze {

    template <typename Type>
    static auto test(int) -> decltype(std::declval<Type>().squeeze());

    template <typename>
    static auto test(...) -> std::false_type;

    enum {
        value = !std::is_same<decltype(test<T>(0)), std::false_type>::value
    };
};

TEST(Chapter06, has_squeeze) {
    ASSERT_EQ(has_squeeze<std::string>::value,  0);
    ASSERT_EQ(has_squeeze<QString>::value,      1);
}

TEST(Chapter06, className) {

    auto className = [](QObject* object) {
        const QMetaObject* metaObject = object->metaObject();
        return metaObject->className();
    };

    MessageQueue* queue = new MessageQueue();
    ASSERT_STREQ(className(queue), "MessageQueue");

    delete queue;
}

TEST(Chapter06, parentClassName) {
    auto parentClassName = [](QObject* object) {
        const QMetaObject* metaObject = object->metaObject();
        const QMetaObject* parentMetaObject = metaObject->superClass();
        return parentMetaObject->className();
    };

    MessageQueue* queue = new MessageQueue();
    ASSERT_STREQ(parentClassName(queue), "QObject");

    delete queue;
}

TEST(Chapter06, checkIsAMethodAvailable) {
    auto isMethodAvailable = [](QObject* object, const char* method) {
        const QMetaObject* metaObject = object->metaObject();
        QString signature = QMetaObject::normalizedSignature(method);
        return metaObject->indexOfMethod(qPrintable(signature)) >= 0;
    };

    MessageQueue* queue = new MessageQueue();
    ASSERT_TRUE(isMethodAvailable(queue, "send(QString)"));

    delete queue;
}

TEST(Chapter06, invokeMethod) {
    QStringList receivedMessages;
    MessageQueue* queue = new MessageQueue();

    QObject::connect(queue, &MessageQueue::messageReceived, [&](const QString& message) {
        receivedMessages << message;
    });

    const QMetaObject* metaObject = queue->metaObject();

    QString message = "new message";
    QStringList expectedMessages = {message};

    metaObject->invokeMethod(queue, "send", Q_ARG(QString, message));

    ASSERT_EQ(receivedMessages, expectedMessages);

    delete queue;
}

TEST(Chapter06, connect) {
    MessageQueue* queue = new MessageQueue();
    Logger* logger = new Logger();

    QStringList expectedMessages{"new message"};

    QObject::connect(queue, &MessageQueue::messageReceived, logger, &Logger::log);

    queue->send("new message");

    ASSERT_EQ(logger->messages(), expectedMessages);

    delete queue;
    delete logger;
}

TEST(Chapter06, setDynamicProperties) {
    MessageQueue* queue = new MessageQueue();
    QString expectedValue = "Any Value";
    queue->setProperty("non-existed-property", expectedValue);

    ASSERT_EQ(queue->property("non-existed-property").toString(), expectedValue);

    delete queue;
}

void removeItemAtObjectList(QObjectList& list, int index) {
    delete list[index];
    list.removeAt(index);
}

TEST(Chapter06, removeItemAtObjectList) {

    QObjectList list;

    for (int i = 0 ; i < 3; i++) {
        list << new QObject();
    }

    for (int i = 0 ; i < 3; i++) {
        removeItemAtObjectList(list, 0);
    }

    ASSERT_EQ(list.size(), 0);
}

TEST(Chapter06, listOfSmartPointer) {
    QList<QSharedPointer<QObject>> list;

    QObject* a = new QObject();

    list.append(QSharedPointer<QObject>(a));

    QPointer<QObject> ptr = a;

    ASSERT_FALSE(ptr.isNull());

    list.clear();

    ASSERT_TRUE(ptr.isNull());
}


inline QVariantMap parse(const QString &text)
{
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(),&jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
            qWarning() << "JSON::parse() error: "<< jsonError.errorString();
    }

    return doc.object().toVariantMap();
}

QString stringify(const QVariantMap &object, bool indented = false)
{
    QJsonObject jsonObject = QJsonObject::fromVariantMap(object);

    QJsonDocument doc;
    doc.setObject(jsonObject);
    QJsonDocument::JsonFormat format = indented ? QJsonDocument::Indented : QJsonDocument::Compact;
    QByteArray bytes = doc.toJson(format);
    return bytes;
}

template <typename T>
QVariantMap serialize(const T& t) {
    QVariantMap ret;
    const QMetaObject metaObject = T::staticMetaObject;
    for (int i = 0 ; i < metaObject.propertyCount(); i++) {
        const QMetaProperty property = metaObject.property(i);
        ret[property.name()] = property.readOnGadget(&t);
    }
    return ret;
}

TEST(Chapter06, serialize) {
    Message message(1, "regular", "content");
    QString expected = "{\"content\":\"content\",\"id\":1,\"type\":\"regular\"}";

    QVariantMap serialized = serialize(message);
    QString json = stringify(serialized);

    ASSERT_EQ(json, expected);
}

template <typename T>
void deserialize(T& t, const QVariantMap& map) {
    const QMetaObject metaObject = T::staticMetaObject;
    for (int i = 0 ; i < metaObject.propertyCount(); i++) {
        const QMetaProperty property = metaObject.property(i);
        if (map.contains(property.name())) {
            property.writeOnGadget(&t, map[property.name()]);
        }
    }
}

TEST(Chapter06, deserialize) {
    QString json = "{\"content\":\"content\",\"id\":1,\"type\":\"regular\"}";
    QVariantMap data = parse(json);
    Message message;
    deserialize(message, data);

    ASSERT_EQ(message.id(),     1);
    ASSERT_EQ(message.type(),   QString("regular"));
    ASSERT_EQ(message.content(), QString("content"));
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
