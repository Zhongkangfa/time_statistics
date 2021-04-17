#include "atimeloggerapi.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

AtimeloggerAPI::AtimeloggerAPI():
    m_interval_url("https://app.atimelogger.com/api/v2/intervals"),
    m_type_url("https://app.atimelogger.com/api/v2/types"),
    reply(nullptr),
    progress_dialog(nullptr)
{
    lastRecordOfTime = 0;
    ExecutionTimes = 0;
}

void AtimeloggerAPI::download(uint from, uint to)
{

    QUrl url = getIntervalUrlWithQuery(from, to);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", getAuthorization());
    reply = networkManager.get(request);

    connect(progress_dialog, SIGNAL(canceled()), reply, SLOT(abort()));
    connect(reply, &QNetworkReply::finished, this, &AtimeloggerAPI::on_finished);

}


void AtimeloggerAPI::on_finished(){
    QNetworkReply::NetworkError downloadError = reply->error();
    if (downloadError == QNetworkReply::NoError)
    {
//        响应：网络连接过程中没有异常
        if (reply->isReadable())
        {
            QJsonArray intervalArray = QJsonDocument::fromJson(reply->readAll())["intervals"].toArray();
            if(intervalArray.isEmpty()){
                reply->deleteLater();
                reply = nullptr;
                progress_dialog->reset();
                progress_dialog->deleteLater();
                progress_dialog = nullptr;
                QMessageBox::about(nullptr, "about","在此时间段内，没有在atimeloggerAPI中找到你记录的数据。");

            }
            else{

                lastRecordOfTime = intervalArray.last()["to"].toDouble();

                if(lastRecordOfTime < aim)
                {
                    download_byte.append(reply->readAll());
                    reply->deleteLater();
                    reply = nullptr;
                    //还没到达终点，再次请求一次
                    ExecutionTimes += 1;
                    QString now = QDateTime::fromSecsSinceEpoch(lastRecordOfTime).toString("yyyy年MM月dd日");
                    QString text =  QString("本次下载了999条数据，下载到：%1，开始第 %2次访问（因为每次最多拿取999条记录）").arg(now).arg(QString::number(ExecutionTimes));
                    progress_dialog->setLabelText(text);
                    download(lastRecordOfTime, aim);
                }
                else if(lastRecordOfTime >= aim)
                {
                    download_byte.append(reply->readAll());
                    reply->deleteLater();
                    reply = nullptr;
                    progress_dialog->reset();
                    progress_dialog->deleteLater();
                    progress_dialog = nullptr;
                    QMessageBox::about(nullptr, "about","一切顺利!");
                }
            }
        }
        else{
            reply->deleteLater();
            reply = nullptr;
            progress_dialog->reset();
            progress_dialog->deleteLater();
            progress_dialog = nullptr;
            QMessageBox::warning(nullptr, "温馨提示", "下载的数据无法读取");
        }
    }
    else if(downloadError == QNetworkReply::AuthenticationRequiredError)
    {
//        响应：账号密码异常
        reply->deleteLater();
        reply = nullptr;
        progress_dialog->reset();
        progress_dialog->deleteLater();
        progress_dialog = nullptr;
        QMessageBox::warning(nullptr, "温馨提示", "账号或密码有误！");
    }
    else if(downloadError == QNetworkReply::OperationCanceledError)
    {
//        响应：人为取消本次下载
        reply->deleteLater();
        reply = nullptr;
        progress_dialog->reset();
        progress_dialog->deleteLater();
        progress_dialog = nullptr;
        QMessageBox::about(nullptr, "about","已成功取消此次行动。");
    }
    else
    {
//        未知的错误
        int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
        reply->deleteLater();
        reply = nullptr;
        progress_dialog->reset();
        progress_dialog->deleteLater();
        progress_dialog = nullptr;
        QMessageBox::warning(nullptr, "错误提示", QString::number(httpCode));
    }

}

void AtimeloggerAPI::visit(uint from, uint to)
{
    download_byte.clear();
    ExecutionTimes = 1;
    progress_dialog = new QProgressDialog("访问中……", "取消此处访问", 0, 0);
    progress_dialog->resize(745, 160);
    progress_dialog->open();

    download(from, to);

}

QByteArray AtimeloggerAPI::getAuthorization()
{
    QString account = "1470298128@qq.com";
    QString password = "948278064";
    QString authorization_string = account + QString(":") + password;
    QByteArray Base64_authorization = authorization_string .toLocal8Bit().toBase64();

    return QString("Basic " + Base64_authorization ).toLocal8Bit();
}

void AtimeloggerAPI::addQueryItems(QUrlQuery &intervalQuery, uint from, uint to)
{
    intervalQuery.addQueryItem("from", QString::number(from));
    intervalQuery.addQueryItem("to", QString::number(to));
    intervalQuery.addQueryItem("limit", "999");
}

QUrl AtimeloggerAPI::getIntervalUrlWithQuery(uint from, uint to)
{
    QUrlQuery intervalQuery;
    addQueryItems(intervalQuery, from, to);

    QUrl intervalUrl(m_interval_url);
    intervalUrl.setQuery(intervalQuery);
    return intervalUrl;
}



void AtimeloggerAPI::work(uint from, uint to)
{
    aim = to;
    visit(from, aim);
}
