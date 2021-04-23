#include "recordrequester.h"
#include "atimeloggerrequest.h"
#include "ui/choosetimedialog.h"

#include "ui/loginscreendialog.h"
#include <QDateTime>
#include <QSqlQuery>
RecordRequester::RecordRequester()
{

}


AtimeloggerRequest RecordRequester::write(QSqlDatabase &db, QString type)
{
    authorization = auth.getAuthorization(db);
    if(!authorization.isEmpty()){
        username = auth.getUsername();
        if(type == "types"){
            return AtimeloggerRequest(username, authorization);
        }else{
            ChooseTimeDialog choosetimedialog;
            choosetimedialog.setLastDateTime(getLastRecordTime(db));
            if(choosetimedialog.exec())
            {
                from = choosetimedialog.from();
                to = choosetimedialog.to();
                return AtimeloggerRequest(username, authorization, from, to);
            }
        }
    }
    return AtimeloggerRequest();
}

AtimeloggerRequest RecordRequester::repeat(uint last)
{
    return AtimeloggerRequest(username, authorization, from, last);
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
    uint last = QDateTime::fromString("2008", "yyyy").toSecsSinceEpoch();
    if(db.open())
    {
        if(db.tables().contains("interval")){
            QSqlQuery query("SELECT [to] FROM [interval] ORDER BY [to] DESC LIMIT 1", db);
            query.next();
            if(!query.value(0).isNull())
            {
                last = query.value(0).toDouble();
            }
        }
        db.close();
    }
    return last;
}

QByteArray RecordRequester::getAuthorization() const
{
    return authorization;
}

QString RecordRequester::getUsername() const
{
    return username;
}

void RecordRequester::saveAuthorization(QSqlDatabase &db)
{
    auth.save(db);
}

void RecordRequester::init()
{
    username.clear();
    authorization.clear();
    auth.init();
}
