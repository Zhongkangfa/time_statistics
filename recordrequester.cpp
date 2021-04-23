#include "recordrequester.h"
#include "atimeloggerrequest.h"
#include "ui/choosetimedialog.h"

#include "ui/loginscreendialog.h"
#include <QDateTime>
#include <QSqlQuery>
RecordRequester::RecordRequester()
{

}


AtimeloggerRequest RecordRequester::write(QSqlDatabase &db)
{
    authorization = auth.getAuthorization(db);
    if(!authorization.isEmpty()){
        username = auth.getUsername();
        ChooseTimeDialog choosetimedialog;
        choosetimedialog.setLastDateTime(getLastRecordTime(db));
        if(choosetimedialog.exec())
        {
            from = choosetimedialog.from();
            to = choosetimedialog.to();
            return AtimeloggerRequest(username, authorization, from, to);
        }
    }
    return AtimeloggerRequest();
}

AtimeloggerRequest RecordRequester::repeat(uint last)
{
    return AtimeloggerRequest(username, authorization, last, to);
}

uint RecordRequester::getFrom() const
{
    return from;
}

uint RecordRequester::getTo() const
{
    return to;
}

uint RecordRequester::getLastRecordTime(QSqlDatabase &db)
{
    if(db.open())
    {
        QSqlQuery query("SELECT [to] FROM [interval] ORDER BY [to] DESC LIMIT 1", db);
        query.next();
        if(query.value(0).isNull())
        {
            return QDateTime::fromString("2008", "yyyy").toSecsSinceEpoch();
        }
        else
        {
            return query.value(0).toDouble();
        }
        db.close();
    }
    return QDateTime::fromString("2008", "yyyy").toSecsSinceEpoch();
}
