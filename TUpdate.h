#ifndef TUPDATE_H
#define TUPDATE_H

#include <QObject>
#include "TConstants.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDir>
#include <QFile>
#include "QProcess"

class TUpdate : public QObject
{
    Q_OBJECT
public:
    explicit TUpdate(QObject *parent = 0);
    bool updateScripts();
    bool checkWorkDirExist();
    QString getLocalVersion();
    QString requestRemoteVersion();

private:
    void compareVersions(QString remoteVersion);
    void downloadScripts();


public slots:
    void endDownloadScripts(QNetworkReply* reply);
    void endGetVersion(QNetworkReply* reply);


};

#endif // TUPDATE_H
