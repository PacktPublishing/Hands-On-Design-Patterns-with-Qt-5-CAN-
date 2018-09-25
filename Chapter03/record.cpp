#include "record.h"

class RecordData : public QSharedData
{
public:
    /* Begin of Custom Code */
    QString id;
    /* End of Custom Code*/
};

Record::Record() : data(new RecordData)
{

}

Record::Record(const Record &rhs) : data(rhs.data)
{

}

Record &Record::operator=(const Record &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Record::~Record()
{

}

/* Begin of New Code */
QString Record::id() const
{
    return data->id;
}

void Record::setId(const QString &id)
{
    data->id = id;
}
/* End of New Code */
