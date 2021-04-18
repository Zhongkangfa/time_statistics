#include "recordrequester.h"
#include "atimeloggerrequest.h"
#include "ui/choosetimedialog.h"
#include "auth.h"
#include "ui/loginscreendialog.h"
RecordRequester::RecordRequester()
{

}

AtimeloggerRequest RecordRequester::write(QSqlDatabase &db)
{
    getAuthorizationAndUsername(db);
    if(hasAuthorizationAndUsername()){
        ChooseLength();
        if(to!=0){
            if(!authorization.isEmpty()){
                return AtimeloggerRequest(username, authorization, from, to);
            }else{
                return AtimeloggerRequest(username, password, from, to);
            }
        }

    }else{
        if(askUsernameAndPassword()){
            ChooseLength();
            if(to!=0){
                if(!authorization.isEmpty()){
                    return AtimeloggerRequest(username, authorization, from, to);
                }else{
                    return AtimeloggerRequest(username, password, from, to);
                }
            }
        }
    }
    return AtimeloggerRequest();
}

AtimeloggerRequest RecordRequester::repeat(uint last)
{
    if(!authorization.isEmpty()){
        return AtimeloggerRequest(username, authorization, last, to);
    }else{
        return AtimeloggerRequest(username, password, last, to);
    }
}

bool RecordRequester::hasAuthorizationAndUsername()
{
    return (!authorization.isEmpty() && !password.isEmpty())  || (!password.isEmpty() && !username.isEmpty());
}

bool RecordRequester::askUsernameAndPassword()
{
    LoginScreenDialog dialog;
    return dialog.exec();
}

void RecordRequester::getAuthorizationAndUsername(QSqlDatabase &db)
{
    Auth auth = Auth();
    authorization = auth.getAuthorization(db);
    if(!authorization.isEmpty()){
        username = auth.getUsername();
    }else{
        username = "";
    }
}

void RecordRequester::ChooseLength()
{
    ChooseTimeDialog choosetimedialog;
    if(choosetimedialog.exec())
    {
        from = choosetimedialog.from();
        to = choosetimedialog.to();
    }else{
        from = 0;
        to = 0;
    }
}


