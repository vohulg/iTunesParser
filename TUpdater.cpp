#include "TUpdater.h"
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>



TUpdater::TUpdater()
{

}

bool TUpdater::updateScripts() {

    //0 check if folder /Users/user/WORK/ exist, if no create so folder ===> 4.
    checkWorkDirExist();
    //1 getLocalVersion
    getLocalVersion();
    //2 getRemoteVersion
    requestRemoteVersion();
    //3. compare versions
    //4. if version diffrent download scripts.zip from server
    //5 remove old scripts folder
    //6 copy newscripts.zip file to work dir
    //7 unzip newscripts.zip
    //8. inform user that scripts was update
    return true;
}

bool TUpdater::checkWorkDirExist(){

    QString workDirPath = QString("%1/%2").arg(QDir::homePath(),WORK_DIR_NAME);
    QString scriptsDirPath = QString("%1/%2/%3").arg(QDir::homePath(),WORK_DIR_NAME,SCRIPTS_DIR_NAME);
    QString tasksDirPath = QString("%1/%2/%3").arg(QDir::homePath(),WORK_DIR_NAME, TASKS_DIR_NAME);

    QDir workDir(workDirPath);
    if(!workDir.exists()){
        workDir.mkdir(workDirPath);
    }

    QDir scriptDir(scriptsDirPath);
    if(!scriptDir.exists()){
        scriptDir.mkdir(scriptsDirPath);
    }

    QDir taskDir(tasksDirPath);
    if(!taskDir.exists()){
        taskDir.mkdir(tasksDirPath);
    }

    return true;

}

QString TUpdater::getLocalVersion(){

    QString version = "";

    QString versionFilePath = QString("%1/%2/%3/%4").arg(QDir::homePath(),WORK_DIR_NAME, SCRIPTS_DIR_NAME,VERSION_FILE_NAME );

    QFile hFile(versionFilePath);

    if(hFile.exists()){

        if(hFile.open(QIODevice::ReadOnly) | QIODevice::Text){
            version = hFile.readLine().trimmed();

        }
    }

    return version;

}

QString TUpdater::requestRemoteVersion() {
/*
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);


    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(endGetVerdion(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl(URL_SCRIPTS_UPDATE_MANIFEST)); // source = url to the file you want to download.
    manager->get(request);

    */


    return "";

}

void TUpdater::finishGetVersion(QNetworkReply *reply)
{
    reply->deleteLater();
    QByteArray version = reply->readAll();

    qDebug() << "remote version is:" << version;


}

void TUpdater::endGetVerdion(QNetworkReply *reply)
{
     qDebug() << "remote version is:";
}
