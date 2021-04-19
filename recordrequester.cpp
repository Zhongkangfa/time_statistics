#include "recordrequester.h"
#include "atimeloggerrequest.h"
#include "ui/choosetimedialog.h"

#include "ui/loginscreendialog.h"
RecordRequester::RecordRequester()
{

}


AtimeloggerRequest RecordRequester::write(QSqlDatabase &db)
{
    authorization = auth.getAuthorization(db);
    if(!authorization.isEmpty()){
        username = auth.getUsername();
        ChooseTimeDialog choosetimedialog;
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
