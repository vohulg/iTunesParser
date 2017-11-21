#include "TBackupSender.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>


TBackupSender::TBackupSender(QObject *parent) : QObject(parent)
{

}

void TBackupSender::tabBarClickedSlot(int tabId)
{
    qDebug() << "clicked TabId:" << tabId;

    if(tabId == TAB_SEND_BACKUP_ID){
        //show all tasks dirs
        showAllTasks();
    }


}

void TBackupSender::showAllTasks(){

    QString taskDirPath = QString("%1/%2/%3").arg(QDir::homePath(), WORK_DIR_NAME, TASKS_DIR_NAME);
    QDir taskDir(taskDirPath);
    QStringList list =  taskDir.entryList();

    foreach(QString dirName,list){
        if(dirName == "." || dirName == ".."){
            list.removeOne(dirName);
            continue;
        }

    }

    comboBoxTasks->addItems(list);






}

void TBackupSender::btnSendBackupClickSlot(bool)
{

    if(comboBoxTasks->currentText().isEmpty()){

        logSendBAckup->append("Не найдено ни одно задание");
        return;
    }

    clean();
    if(!setUrlAndGuid()){
        return;
    }

    QStringList targetList = getTargetAppList();
    if(targetList.isEmpty()){
        logSendBAckup->append("Не найдено ни одного бэкапа");
        return;
    }

    btnSendBackup->setEnabled(false);

    runSendProc(targetList);



}

void TBackupSender::endSendBackUp(){

     btnSendBackup->setEnabled(true);
     logSendBAckup->append("Отправка заврешена");
}

void TBackupSender::clean()
{
    targetAppsList.clear();
    currentGuid.clear();
    currentUrl.clear();
}



void TBackupSender::runSendProc(QStringList targetApps){

    if(targetApps.isEmpty()){
        qDebug() << "NO targetApps";
        return;
    }

    logSendBAckup->append(QString("Идет отправка файла %1 ...").arg(targetApps.at(0)));

    QString zipPath = targetApps.at(0);
    QString url = getCurrentUrl();
    QString guid = getCurrentGuid();
    QString uuid = DEFAULT_UUID;

    QProcess* zipProc = new QProcess(this);
    QObject::connect(zipProc, SIGNAL(finished(int,QProcess::ExitStatus)),
                         this, SLOT(finishSendBackup(int, QProcess::ExitStatus)));

    QString cmd = "/usr/local/bin/sender";
    QStringList argZip;
    argZip << zipPath << url << guid << uuid;
    zipProc->start(cmd, argZip);
}

QStringList TBackupSender::getTargetAppList(){

    targetAppsList.clear();

   QString taskFullPath = QString("%1/%2/%3/%4").arg(QDir::homePath(),WORK_DIR_NAME, TASKS_DIR_NAME, comboBoxTasks->currentText());

   QDir taskDir(taskFullPath);

   QStringList taskDirContentList = taskDir.entryList();

   foreach (QString fname, taskDirContentList) {
       if(fname.contains(FILENAME_WHATSAPP_ZIP) || fname.contains(FILENAME_WECHAT_ZIP)){
           targetAppsList << QString("%1/%2").arg(taskFullPath,fname);
       }
   }

   return targetAppsList;


}

bool TBackupSender::setUrlAndGuid()
{

    QString fileWithGuid = QString("%1/%2/%3/%4/%5/%6/%7").arg(QDir::homePath(),WORK_DIR_NAME, TASKS_DIR_NAME, comboBoxTasks->currentText(), SCRIPTS_DIR_NAME, CREATE_IPA_DIR_NAME,GUID_FILENAME);

    QFile fileGuid(fileWithGuid);
    if (!fileGuid.open(QIODevice::ReadOnly)){
        logSendBAckup->append("Файл с guid не найден");
        return false;
    }

    fileGuid.readLine().trimmed();// read alias, not used

    //get guid
    QString guid = fileGuid.readLine().trimmed();
    if(guid.length() != GUID_LEN){
        logSendBAckup->append("В файле  с guid не найден guid");
        return false;
    }

    qDebug() << "Guid is " << guid;
    logSendBAckup->append(QString("Guid is %1").arg(guid));

    setCurrentGuid(guid);

     //get url
    QString url = fileGuid.readLine().trimmed();
    if(url.length() < 5 || !url.contains("http")){
        logSendBAckup->append("В файле  с guid не найден url");
        return false;
    }
    setCurrentUrl(url);

    return true;

}

void TBackupSender::finishSendBackup(int, QProcess::ExitStatus)
{
    if(targetAppsList.count() > 0){
        targetAppsList.removeAt(0);
    }

    if(targetAppsList.isEmpty()){
        endSendBackUp();
        return;
    }


    runSendProc(targetAppsList);

}

QString TBackupSender::getCurrentGuid() const
{
    return currentGuid;
}

void TBackupSender::setCurrentGuid(const QString &value)
{
    currentGuid = value;
}

QString TBackupSender::getCurrentUrl() const
{
    return currentUrl;
}

void TBackupSender::setCurrentUrl(const QString &value)
{
    currentUrl = value;
}

