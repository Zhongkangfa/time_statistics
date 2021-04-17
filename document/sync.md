我想了解如何从atimelogger提供的API获取数据，我该阅读哪些文件？

infrastructure/atimeloggerapi.h

该实例对象名称是？

atimelogger

访问入口是？

通过菜单栏出发点击事件，回调visit()函数，请从AtimeloggerAPI::visit函数开始阅读。

```c++
connect(ui->actionSycn, &QAction::triggered, atimelogger, &AtimeloggerAPI::visit);
```

该程序的下载流程是？或者说它是如何工作的？

通过visit()获取开始时间和结束时间；

根据获取的时间，执行download()去atimelogger提供的API上下载。

```c++
//创建请求
QNetworkRequest request(getIntervalUrlWithQuery(from, to));
request.setRawHeader("Authorization", getAuthorization());
//发送请求
reply = networkManager.get(request);
//回调函数：响应事件
connect(reply, &QNetworkReply::finished, this, &AtimeloggerAPI::on_finished);
```

接下在的重点是什么？

查看响应事件的回调函数。



为什么要将QProgressDialog设置为指针变量？在函数中创建不好吗？

因为我执行的是异步程序，如果将QProgressDialog实例创建在函数中，当我发送请求后，QProgressDialog实例会随着函数的结束而销毁，从而无法响应回调函数。与生命周期有关。

## 遇到的意料之外的问题

```c++
QDateTime now;
now.setSecsSinceEpoch(lastRecordOfTime);
QString text =  QString("本次下载了999条数据，下载到：%1，开始第 %2次访问（因为每次最多拿取999条记录）").arg(now.toString("yyyy年MM月dd日")).arg(QString::number(ExecutionTimes));
```

通过测试，lastRecordOfTime变量确实在变化。

啊哈！因为我测试用的时间是跨度太小了，不足以改变日期。不管怎么计算，还是没有走出这个日期。