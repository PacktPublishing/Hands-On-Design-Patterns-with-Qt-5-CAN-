#ifndef RECORD_H
#define RECORD_H

#include <QSharedDataPointer>

class RecordData;

class Record
{
public:
    Record();
    Record(const Record &);
    Record &operator=(const Record &);
    ~Record();

    /* Begin of Custom Code */
    QString id() const;
    void setId(const QString &id);
    /* End of Custom Code */

private:
    QSharedDataPointer<RecordData> data;
};

#endif // RECORD_H
