#ifndef TUPDATER_H
#define TUPDATER_H

#include <QObject>
#include "TConstants.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class TUpdater : QObject
{
    Q_OBJECT

public:
    TUpdater();
    bool updateScripts();
    bool checkWorkDirExist();
    QString getLocalVersion();
    QString requestRemoteVersion();

private:
    void endGetVerdion(QNetworkReply* reply);

public slots:
    void finishGetVersion(QNetworkReply* reply);



};

#endif // TUPDATER_H
