#ifndef TIMERECORDS_H
#define TIMERECORDS_H

#include <QObject>

class TimeRecords: public QObject
{
    Q_OBJECT
public:
    TimeRecords();
    //virtual ~TimeRecords()=0;

    //Retrieve or Query
    virtual uint getLastRecordTime()=0;

    //Create


    //Update
    virtual void insertTimeRecords(QJsonArray intervalArray)=0;
};

#endif // TIMERECORDS_H
