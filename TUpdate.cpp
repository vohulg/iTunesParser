#include "TUpdate.h"

TUpdate::TUpdate(QObject *parent) : QObject(parent)
{

}

bool TUpdate::updateScripts() {

    //0 check if folder /Users/user/WORK/ exist, if no create so folder ===> 4.
    checkWorkDirExist();
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

bool TUpdate::checkWorkDirExist(){

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

QString TUpdate::getLocalVersion(){

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

QString TUpdate::requestRemoteVersion() {

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);


    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(endGetVersion(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl(URL_SCRIPTS_UPDATE_MANIFEST)); // source = url to the file you want to download.
    manager->get(request);


    return "";

}

void TUpdate::compareVersions(QString remoteVersion)
{

    QString localVer = getLocalVersion();

    int resCompare = QString::compare(localVer, remoteVersion, Qt::CaseInsensitive);

    qDebug() << "compare result is:" << resCompare;

    if(resCompare != VERSIONS_EQUAL){

        //1 Download scripts.zip
        downloadScripts();

    }

}

void TUpdate::downloadScripts()
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(endDownloadScripts(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl(URL_SCRIPTS_UPDATE_BACKUP));
    manager->get(request);




}

void TUpdate::endDownloadScripts(QNetworkReply *reply)
{
    reply->deleteLater();
    QByteArray scriptsZip = reply->readAll();

    QString dstPath =  QString("%1/%2/%3").arg(QDir::homePath(),WORK_DIR_NAME,REMOTE_SCRIPTS_ZIP_NAME);

    QFile hFile(dstPath);

    if(!hFile.open(QFile::WriteOnly)){

        qDebug() << "File not opened";
        emit finishUpdate(1);
        return;
    }

    //save to file
    int byteCount = hFile.write(scriptsZip);
    qDebug() << byteCount<< " bytes written to file";
    if(byteCount == 0){
        qDebug() << "Faild write zip file";
        emit finishUpdate(1);
        return;
    }


    //1.remove older scripts folder
    QString scriptsDirPath = QString("%1/%2/%3").arg(QDir::homePath(),WORK_DIR_NAME,SCRIPTS_DIR_NAME);
    QDir dir(scriptsDirPath);
    dir.removeRecursively();

    //2. unzip dir
    QProcess* zipProc = new QProcess(this);
    QString cmd = "/usr/bin/unzip";

    QStringList argZip;
    argZip << dstPath;
    zipProc->setWorkingDirectory(QString("%1/%2").arg(QDir::homePath(),WORK_DIR_NAME));
     zipProc->start(cmd, argZip);


    if (!zipProc->waitForFinished()){
       qDebug() <<  zipProc->errorString();
        emit finishUpdate(1);
        return ;
    }

    qDebug() << zipProc->readAll();

    //3.remove
    QFile hTmpFile(dstPath);
    hTmpFile.remove();


    //4.remove __MACOS
    QDir dirMacMeta(QString("%1/%2/%3").arg(QDir::homePath(),WORK_DIR_NAME,UNZIP_META));
    dirMacMeta.removeRecursively();
    emit finishUpdate(0);



}

void TUpdate::endGetVersion(QNetworkReply *reply)
{
    reply->deleteLater();
    QByteArray remoteVersionByteArr = reply->readAll();
    compareVersions(remoteVersionByteArr);



}
