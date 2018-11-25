#pragma once
#include <QObject>

class StudentInfo
{
    Q_GADGET
    Q_PROPERTY(QString studentId MEMBER studentId)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(int age MEMBER age)

public:
    QString studentId;
    QString name;
    int age;
};

