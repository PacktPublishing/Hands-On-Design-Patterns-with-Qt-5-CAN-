#pragma once
#include <QObject>

class StudentInfo
{
    Q_GADGET
    Q_PROPERTY(QString studentId MEMBER studentId)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(Sex sex MEMBER sex)

public:
    typedef enum { Male, Female} Sex;
    QString studentId;
    QString name;
    Sex sex;
};

