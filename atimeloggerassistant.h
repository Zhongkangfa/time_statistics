#ifndef ATIMELOGGERASSISTANT_H
#define ATIMELOGGERASSISTANT_H

#include <QObject>

class AtimeloggerAssistant : public QObject
{
    Q_OBJECT
public:
    explicit AtimeloggerAssistant(QObject *parent = nullptr);
private:

private slots:
    void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void on_finished();
signals:

};

#endif // ATIMELOGGERASSISTANT_H
