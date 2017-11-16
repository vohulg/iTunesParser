#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "QDebug"
#include "QFileDialog"
#include "QMessageBox"

//#define TEST

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //check new version of scripts
    TUpdater updater;
    updater.updateScripts();

   setBackUpRootPath();
   showAllBackups();
   logTextBrowser = ui->logTextBrowser;
   logTextBrowser->append("1. Загрузите файс с номером задания");
   ui->startBtn->setEnabled(false);
   WHATSAPP_DB_FILENAME = "ChatStorage.sqlite";
   WHATSAPP_MEDIA_ZIP_FILENAME = "wmedia.zip";
   WHATSAPP_MEDIA_ZIP_POST_NAME = "wzipfile";
   WHATSAPP_DB_POST_NAME = "wdbfile";
   IPA_BUILDER_MAC_SERVER_IP = "http://88.204.154.151";
   INSTALL_URL = "https://xargon.ru/install";

   WECHAT_DB_FILE = "wechat_dbfile.zip";
   WECHAT_POST_NAME = "wechat_zip";

   VIBER_DB_FILE = "viber_dbfile.zip";
   VIBER_POST_NAME = "viber_zip";

   MAX_BYTE_PERMIT_FOR_BACKUP = 1773741824; //1.7 GB
   SIZE_OF_BACKUP_VERY_BIG = 500000000; // 600Mb

   ALERT_STR = "PARSING_BREAKING";



    /*
   APPLE_ID = "";
   APPLE_ID_PASS = "";
   KEYCHAIN_PASS = "";
   */

   ui->btnOpenReadyIpaDir->setEnabled(false);



   //instructionForm.setUrl("http://88.204.154.151");
    // instructionForm.show();



    //runTest();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showAllBackups(){

    QDir backupDir(pathToAllBackup);
    QStringList list =  backupDir.entryList();

    foreach(QString dirName,list){
        if(dirName == "." || dirName == ".."){
            list.removeOne(dirName);
            continue;
        }
        qDebug() << "dirName:" << dirName;
    }

   ui->backupsListComBox->addItems(list);


}

void MainWindow::setBackUpRootPath(){

#if (defined (Q_OS_MAC32) || defined (Q_OS_MAC64))
    pathToAllBackup = QString("%1/Library/Application Support/MobileSync/Backup").arg(QDir::homePath());
#else
    pathToAllBackup = QString("%1/AppData/Roaming/Apple Computer/MobileSync/Backup").arg(QDir::homePath());
#endif

}

void MainWindow::startCreateApp()
{
    if(!checkPreParsing()){
        return;
    }

    parseWhatsApp();






}

 bool MainWindow::checkPreParsing(){

     ui->startBtn->setEnabled(false);
     logTextBrowser->append("\nОбработка бэкапа.........");
     setUpdatesEnabled(true);
     repaint();

     QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), MANIFEST_NAME );
      connectDatabase(manifestPath);

      UUID = ui->backupsListComBox->currentText();

     // if(UUID.isEmpty() || UUID.trimmed().length() != UUID_LENTH){
      if(UUID.isEmpty()){
          ui->startBtn->setEnabled(true);
          ui->backupsListComBox->setStyleSheet("QComboBox { border-style: outset;border-width: 1px; border-color: red; }");
          QMessageBox msgBox;
          msgBox.setText("Введите корректный UUID устройства длиной 40 символов ");
          msgBox.exec();
          return false;
      }

      ui->backupsListComBox->setStyleSheet("QComboBox { border-style: outset;border-width: 0px; border-color: black; }");
      //clear all tmpDir
      clear();

      return true;


 }

 void MainWindow::parseWechatApp(){

     setCURRENT_PARSED_APP_ID(WECHAT_ID);

      if(!ui->WechatAppCheckBox->isChecked()){
          setRESULT_PARSING(RESULT_APP_NOT_CHECKED);
          endParseApp(0,QProcess::NormalExit);
          return;
      }

      QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), MANIFEST_NAME );
      processWechatBackup(manifestPath);

 }

  void MainWindow::parseWhatsApp() {

      setCURRENT_PARSED_APP_ID(WHATSAPP_ID);

       if(!ui->whatsappAppcheckBox->isChecked()){
           setRESULT_PARSING(RESULT_APP_NOT_CHECKED);
           endParseApp(0,QProcess::NormalExit);
           return;
       }

       QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), MANIFEST_NAME );
       processWhatsappBackup(manifestPath);


  }

void MainWindow::on_startBtn_clicked()
{


    startCreateApp();
    return;

    //ui->startBtn->setText("Ждите...");
    ui->startBtn->setEnabled(false);
    logTextBrowser->append("\nОбработка бэкапа.........");

     setUpdatesEnabled(true);
     repaint();



    QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), MANIFEST_NAME );
     connectDatabase(manifestPath);

    UUID = ui->backupsListComBox->currentText();

   // if(UUID.isEmpty() || UUID.trimmed().length() != UUID_LENTH){
    if(UUID.isEmpty()){
        ui->startBtn->setEnabled(true);
        ui->backupsListComBox->setStyleSheet("QComboBox { border-style: outset;border-width: 1px; border-color: red; }");
        QMessageBox msgBox;
        msgBox.setText("Введите корректный UUID устройства длиной 40 символов ");
        msgBox.exec();
        return;
    }

    ui->backupsListComBox->setStyleSheet("QComboBox { border-style: outset;border-width: 1px; border-color: black; }");


     QMap <QString, QString> *mapPostAndFilePaths =new QMap<QString, QString>();

     //clear all tmpDir
     clear();



     if(ui->whatsappAppcheckBox->isChecked()){
         logTextBrowser->append("\nИдет Обработка файлов для мессенджера Whatsapp.........");
          repaint();
         QString zipPath =  processWhatsappBackup(manifestPath);
         if(!zipPath.isEmpty()){

             if(!zipPath.contains(ALERT_STR)){

                 //add ChatStrorage.sqlite
                 mapPostAndFilePaths->insert(WHATSAPP_MEDIA_ZIP_POST_NAME,zipPath);

                 //add ChatStrorage.sqlite
                 QString dbFileNameFullPath = zipPath;
                 dbFileNameFullPath.replace(WHATSAPP_MEDIA_ZIP_FILENAME, WHATSAPP_DB_FILENAME);
                 mapPostAndFilePaths->insert(WHATSAPP_DB_POST_NAME,dbFileNameFullPath);
             }

             else {
                 ui->whatsappAppcheckBox->setChecked(false);
             }


         }

         else {
             QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Внимание",
                                                                             tr("Внимание! Не найден бэкап Whatsapp. Переписка не будет восстановлена при замене приложения. Продолжить формирование приложений ?"),
                                                                             QMessageBox::No | QMessageBox::Yes,
                                                                             QMessageBox::No);
             if(resBtn == QMessageBox::No) {
                 logTextBrowser->append("\nФормирование пакетов прекращено.");
                 ui->guidLine->clear();
                  logTextBrowser->clear();
                 clear();
                 return;
             }

         }



     }


     if(ui->WechatAppCheckBox->isChecked()){
         logTextBrowser->append("\nИдет Обработка файлов для мессенджера Wechat.........");
          repaint();
         QString zipPath =  processWechatBackup(manifestPath);
         if(!zipPath.isEmpty()){
             if(!zipPath.contains(ALERT_STR)){
                 mapPostAndFilePaths->insert(WECHAT_POST_NAME,zipPath);
             }
             else {
                 ui->WechatAppCheckBox->setChecked(false);
             }
         }
         else {
                 QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Внимание",
                                                                                 tr("Внимание! Не найден бэкап Wechat. Переписка не будет восстановлена при замене приложения. Все равно продолжить формирование пакета ?"),
                                                                                 QMessageBox::No | QMessageBox::Yes,
                                                                                 QMessageBox::No);
                 if(resBtn == QMessageBox::No) {
                     logTextBrowser->append("\nФормирование пакетов прекращено.");
                     ui->guidLine->clear();
                     logTextBrowser->clear();

                    // showAlertWithMsg("Внимание! Не найден бэкап Wechat. Переписка не будет восстановлена при замене приложения. Все равно продолжить формирование пакета ?");
                     clear();
                     return;
                 }
         }
     }

     if(ui->ViberAppCheckBox->isChecked()){
         logTextBrowser->append("\nИдет Обработка файлов для мессенджера VIBER.........");
          repaint();
         QString zipPath =  processViberBackup(manifestPath);
         if(!zipPath.isEmpty()){
             mapPostAndFilePaths->insert(VIBER_POST_NAME,zipPath);
         }
         else {
                 QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Внимание",
                                                                                 tr("Внимание! Не найден бэкап VIBER. Переписка не будет восстановлена при замене приложения. Все равно продолжить формирование пакета ?"),
                                                                                 QMessageBox::No | QMessageBox::Yes,
                                                                                 QMessageBox::No);
                 if(resBtn == QMessageBox::No) {
                     logTextBrowser->append("\nФормирование пакетов прекращено.");
                     ui->guidLine->clear();
                     logTextBrowser->clear();

                     showAlertWithMsg("Внимание! Не найден бэкап Wechat. Переписка не будет восстановлена при замене приложения");
                     clear();
                     return;
                 }
         }

     }



#if (defined (Q_OS_MAC32) || defined (Q_OS_MAC64))
     createLocalIpa(mapPostAndFilePaths, UUID);
#else
     // for windows
     createRemoteIpa(mapPostAndFilePaths, UUID);

#endif




}



void MainWindow::showAlertWithInfoMsg(QString message){

    QMessageBox::StandardButton resBtn = QMessageBox::information( this, "Внимание",
                                                                    message,
                                                                    QMessageBox::Cancel,
                                                                    QMessageBox::Cancel);
    if(resBtn == QMessageBox::Cancel) {
        logTextBrowser->append("\nФормирование пакетов прекращено.");
        ui->guidLine->clear();
        logTextBrowser->clear();

}

}

QString MainWindow::getBackupTmpDirFullPath_ForResult()
{
    QString tempDirPath = QString("%1/%2-result").arg(QDir::tempPath(), UUID);
    QDir tmpDir(tempDirPath);

    if(!tmpDir.exists()){
        bool isSuccess = tmpDir.mkdir(tempDirPath);
        if(!isSuccess){
            qDebug() << "faild create temp folder at path" << tempDirPath;
           return "";
        }
    }

    qDebug() << "Dir for result is :" << tempDirPath;
    return tempDirPath;
}

void MainWindow::moveBackupsToResultFolder()
{
    QString dstDir = getBackupTmpDirFullPath_ForResult();
    QString srcDir = getBackupTmpDirFullPath();

    QDir dir(srcDir);
    QStringList list =  dir.entryList();

    foreach(QString dirName,list){
        if(dirName == "." || dirName == ".."){
            continue;
        }

        //write to lst file
        QString srcFullPath = QString("%1/%2").arg(srcDir, dirName);
        if(srcFullPath.contains(WHATSAPP_DB_FILENAME) || srcFullPath.contains(WHATSAPP_MEDIA_ZIP_FILENAME) || srcFullPath.contains(WECHAT_DB_FILE) ){
           QString dstFullPath = QString("%1/%2").arg(dstDir, dirName);
           QFile file(srcFullPath);
           file.rename(srcFullPath,dstFullPath);
        }


    }

    //clear folder

    if (dir.exists(srcDir)){
        QDir dirForRemove(srcDir);
        dirForRemove.removeRecursively();
    }




}

void MainWindow::createLocalIpa(QMap <QString, QString>* mapPostAndFilePath, QString uuid)
{
    //1.Copy script folders from /Users/maxudin/WORK/script to dir with backup files
    copyScripts();
    //2. Create guid.info file and send to ./script/create_ipa
    createGuidFile();
    //2.1 Copy backups to workdir
    copyBackupsToWorkDir();
    //3. get profiles for all applications

    getProfiles();
    //4. start vg_modify_app for all checked applications

}

void MainWindow::createRemoteIpa(QMap <QString, QString>* mapPostAndFilePaths, QString uuid)
{
    sendAllBackup(mapPostAndFilePaths, UUID);

}

bool MainWindow::copyScripts()
{

    QString srcDir = QString("%1/WORK/scripts").arg(QDir::homePath());
    //QString dstDir = getBackupTmpDirFullPath_ForResult();
    QString dstDir = getCurrentWorkDir();

    QProcess* zipProc = new QProcess(this);
    QString cmd = "/bin/cp";

    QStringList argZip;
    argZip << "-r" << srcDir << dstDir;
     zipProc->start(cmd, argZip);

    if (!zipProc->waitForFinished())
        return false;

    QByteArray copyResult = zipProc->readAll();

    //check if dir exist
    QDir dir(QString("%1/scripts").arg(getCurrentWorkDir()));
    if(dir.exists()){
        return true;
    }
    else{
        QString log = QString("Не удалось скопировать папку %1 в %2. Результат ошибки: %3").arg(srcDir, dstDir, copyResult);
        ui->logTextBrowser->append(log);
        return false;
    }



}

bool MainWindow::createGuidFile()
{
    QString guidFilePath = QString("%1/scripts/createIpa/guid.info").arg(getCurrentWorkDir());

    qDebug() << "guidFilePath:" << guidFilePath;

    QFile fileGuid(guidFilePath);

    //QFile fileGuid("/Users/maxudin/common/guid.info");

    if (!fileGuid.open(QIODevice::WriteOnly)){
        QString log = QString("Не удалось создать файл по пути %1 для записи guid с ошибкой %2").arg(guidFilePath, fileGuid.errorString());
        ui->logTextBrowser->append(log);
        return false;
    }

    QTextStream out(&fileGuid);
    out << "not used line: " << "\n";
    out << GUID_BYTEARR << "\n";
    out << URL_BYTEARR << "\n";

    fileGuid.close();

    return true;

}

bool MainWindow::copyBackupsToWorkDir()
{

    QDir tmpDir(getBackupTmpDirFullPath_ForResult());
    QStringList list = tmpDir.entryList();

    foreach (QString fileName, list) {

        if(fileName == "." || fileName == ".."){
            continue;
        }


        QString srcFullPath = QString("%1/%2").arg(getBackupTmpDirFullPath_ForResult(), fileName);
        QString dstFullPath = QString("%1/%2").arg(getCurrentWorkDir(), fileName);

        QFile file(srcFullPath);
        file.rename(dstFullPath);



    }

    return true;

}

bool MainWindow::getProfiles()
{
    logTextBrowser->append("Идет процесс получения ключей подписи ......");

    QString rubyScriptPatch = QString("%1/scripts/changeProfile.rb").arg(getCurrentWorkDir());


    QString login = APPLE_ID;
    QString secWord = APPLE_ID_PASS;

    QMap<QString, QString> mapApps = getMapForCheckedApps();
    QMapIterator<QString, QString> iter(mapApps);

    PROCESS_FETCH_PROFILE_COUNTS = 0;

    while (iter.hasNext()) {

        iter.next();

        QString dstProfilePath = QString("%1/scripts/profile/%2").arg(getCurrentWorkDir(), iter.value());
        QString appId = iter.key();

        qDebug() << "Start ruby script for appId" << appId;

        QProcess* zipProc = new QProcess(this);

        //connect
        QObject::connect(zipProc, SIGNAL(finished(int,QProcess::ExitStatus)),
                             this, SLOT(finishFetchProfile(int, QProcess::ExitStatus)));


        QString cmd = "/usr/local/bin/ruby";

        QStringList argZip;
        argZip << rubyScriptPatch << UUID << UUID << appId << login << secWord << dstProfilePath;

        QString testCmd = QString("%1 %2 %3 %4 %5 %6 %7 %8").arg(cmd, rubyScriptPatch, UUID, UUID, appId, login, secWord, dstProfilePath);
        qDebug() << "cmd line is:" << testCmd;

        zipProc->start(cmd, argZip);
        PROCESS_FETCH_PROFILE_COUNTS++;

        //if (!zipProc->waitForFinished())
         //  return false;



    }

}

bool MainWindow::runVgModifyScript()
{
     qDebug() << "runVgModifyScript running....";
     logTextBrowser->append("Идет формирование установочных пакетов ......");

    //$BASE_PATH/scripts/createIpa/vg_modify_app w $BASE_PATH Aqwer123$ /Users/admin/Library/Keychains/login.keychain 1b5b94b83e762264209e8482ff965434f0dcd1ab
  QString basePath = getCurrentWorkDir();

  QMap<QString, QString> mapApps = getMapForCheckedApps();
  QMapIterator<QString, QString> iter(mapApps);

  PROCESS_MODIFY_APP = 0;

  while (iter.hasNext()) {

      iter.next();

      QString appId = iter.key();

      QProcess* zipProc = new QProcess(this);

      //connect
      QObject::connect(zipProc, SIGNAL(finished(int,QProcess::ExitStatus)),
                           this, SLOT(finishModifyApp(int, QProcess::ExitStatus)));


      QString cmd = QString("%1/scripts/createIpa/vg_modify_app").arg(getCurrentWorkDir());

      QStringList argZip;
      argZip << getAppLetterFromAppId(appId) << basePath << KEYCHAIN_PASS << QString("%1/Library/Keychains/login.keychain").arg(QDir::homePath()) << UUID;

      QString testCmd = QString("%1 %2 %3 %4 %5 %6").arg(cmd, getAppLetterFromAppId(appId), basePath, KEYCHAIN_PASS, QString("%1/Library/Keychains/login.keychain").arg(QDir::homePath()), UUID);
      qDebug() << "cmd line is:" << testCmd;

      zipProc->start(cmd, argZip);
      PROCESS_MODIFY_APP++;





  }


}

bool MainWindow::openIpaInFileManager()
{

   QString filter = "Any files (*)";
   QString* selecFilter = &filter;
   QString fileWithGuid = QFileDialog::getOpenFileName(this, tr("Open image file"), tr("/"), filter, selecFilter, QFileDialog::DontConfirmOverwrite );



}

void MainWindow::informPathOfReadyIpa()
{
    ui->btnOpenReadyIpaDir->setEnabled(true);
    QString ipaDir = QString("%1/scripts/ipa").arg(getCurrentWorkDir());
    QString informLog = QString("\n\nВсе пакеты сформированы и находятся в директории %1. \n Откройте программу Xcode,  Меню Window->Devices->Add(+)Applications и установите все сформированные пакеты").arg(ipaDir);

    ui->logTextBrowser->append(informLog);
}

QString MainWindow::getCurrentWorkDir()
{
    if(GUID_BYTEARR.isEmpty() || GUID_BYTEARR.isNull()){
        ui->logTextBrowser->append("Не найден guid задания");
        return "";
    }

    if(CURRENT_WORK_DIR.isEmpty() || CURRENT_WORK_DIR.isNull()){

        QDateTime dTime(QDateTime::currentDateTime());
        QString currTime = dTime.toString("dd_MM_yyyy_HH_mm_ss");
        QString dirName = QString("{%1+%2}").arg(currTime,QString::fromStdString(GUID_BYTEARR.data()));

        //QString dirName = dTime.toString("HHmmss");
        QString workPath = QString("%1/WORK/tasks/%2").arg(QDir::homePath(), dirName);

        QDir dir;
        bool res = dir.mkpath(workPath);

        if(res){
           CURRENT_WORK_DIR = workPath;

        }

    }

    return CURRENT_WORK_DIR;
}

QMap<QString, QString> MainWindow::getMapForCheckedApps()
{

   QMap <QString, QString> mapAppInfo;

    if(ui->whatsappAppcheckBox->isChecked()){
        mapAppInfo.insert("net.whatsapp.vg","whatsapp.mobileprovision");
    }

    if(ui->TelegramAppCheckBox->isChecked()){
        mapAppInfo.insert("com.telegram.vg","telegram.mobileprovision");
    }

    if(ui->WechatAppCheckBox->isChecked()){
        mapAppInfo.insert("com.tencent.vg","wechat.mobileprovision");
    }

    return mapAppInfo;
}

QString MainWindow::getAppLetterFromAppId(QString appId)
{
    if(appId.contains("whatsapp")){
        return "w";
    }

    else if(appId.contains("tencent")){
        return "c";
    }

    else if(appId.contains("telegra")){
        return "t";
    }

}

QMap<QString, QString> MainWindow::getMAP_POST_AND_FILE_PATHS() const
{
    return MAP_POST_AND_FILE_PATHS;
}

void MainWindow::setMAP_POST_AND_FILE_PATHS(const QMap<QString, QString> &value)
{
    MAP_POST_AND_FILE_PATHS = value;
}

QString MainWindow::getCURRENT_ZIPPED_FILE_PATH() const
{
    return CURRENT_ZIPPED_FILE_PATH;
}

void MainWindow::setCURRENT_ZIPPED_FILE_PATH(const QString &value)
{
    CURRENT_ZIPPED_FILE_PATH = value;
}

int MainWindow::getRESULT_PARSING() const
{
    return RESULT_PARSING;
}

void MainWindow::setRESULT_PARSING(int value)
{
    RESULT_PARSING = value;
}

int MainWindow::getCURRENT_PARSED_APP_ID() const
{
    return CURRENT_PARSED_APP_ID;
}

void MainWindow::setCURRENT_PARSED_APP_ID(int value)
{
    CURRENT_PARSED_APP_ID = value;
}

QString MainWindow::getGUID_FILE_PATH() const
{
    return GUID_FILE_PATH;
}

void MainWindow::setGUID_FILE_PATH(const QString &value)
{
    GUID_FILE_PATH = value;
}

void MainWindow::finishFetchProfile(int exitCode, QProcess::ExitStatus status)
{
    qDebug() << "processFinish with status:" << status;
    PROCESS_FETCH_PROFILE_COUNTS--;

    if(PROCESS_FETCH_PROFILE_COUNTS == 0){
      qDebug() << "All profiles fetched";
      //start vg_modify_app

      runVgModifyScript();

    }
}

void MainWindow::finishModifyApp(int, QProcess::ExitStatus)
{
    qDebug() << "finishModifyApp run";
    PROCESS_MODIFY_APP--;

    if(PROCESS_MODIFY_APP == 0){
         qDebug() << "All apps modified";
        informPathOfReadyIpa();
    }

}

void MainWindow::checkWechatAppResult(){

    int resultCode = getRESULT_PARSING();

    if(resultCode == RESULT_ZIP_IS_SUCCESS){
        moveBackupsToResultFolder();
        QString zipPath = QString("%1/%2").arg(getBackupTmpDirFullPath_ForResult(),WECHAT_DB_FILE );

        QFile zipFile(zipPath);
        if(!zipFile.exists()){

            QString message = "Внимание! Не найден бэкап Wechat. Переписка не будет восстановлена при замене приложения";
            QMessageBox::StandardButton resBtn = QMessageBox::information( this, "Внимание",
                                                                            message,
                                                                            QMessageBox::Cancel,
                                                                            QMessageBox::Cancel);
            return;
        }

        MAP_POST_AND_FILE_PATHS.insert(WECHAT_POST_NAME,zipPath);

        qDebug() << "zipPath:" << zipPath;

    }


}

void MainWindow::checkWhatsAppResult(){

    int resultCode = getRESULT_PARSING();

    if(resultCode == RESULT_ZIP_IS_SUCCESS){
        moveBackupsToResultFolder();
        QString zipPath = QString("%1/%2").arg(getBackupTmpDirFullPath_ForResult(),WHATSAPP_MEDIA_ZIP_FILENAME );

        QFile zipFile(zipPath);
        if(!zipFile.exists()){

            QString message = "Внимание! Не найден бэкап Whatsapp. Переписка не будет восстановлена при замене приложения";
            QMessageBox::StandardButton resBtn = QMessageBox::information( this, "Внимание",
                                                                            message,
                                                                            QMessageBox::Cancel,
                                                                            QMessageBox::Cancel);
            return;
        }

        MAP_POST_AND_FILE_PATHS.insert(WHATSAPP_MEDIA_ZIP_POST_NAME,zipPath);

        //add ChatStrorage.sqlite
        QString dbFileNameFullPath = zipPath;
        dbFileNameFullPath.replace(WHATSAPP_MEDIA_ZIP_FILENAME, WHATSAPP_DB_FILENAME);
        MAP_POST_AND_FILE_PATHS.insert(WHATSAPP_DB_POST_NAME,dbFileNameFullPath);

        qDebug() << "zipPath:" << zipPath;

    }







}

void MainWindow::endParseApp(int, QProcess::ExitStatus)
{

    int currentApp = getCURRENT_PARSED_APP_ID();

    //first run
    if(currentApp == WHATSAPP_ID){
       checkWhatsAppResult();
       parseWechatApp();
    }

    //second run
    else if(currentApp == WECHAT_ID){
        checkWechatAppResult();
        buildIpa(); // run this for last application

    }

}

void MainWindow::buildIpa(){

#if (defined (Q_OS_MAC32) || defined (Q_OS_MAC64))
     createLocalIpa(&MAP_POST_AND_FILE_PATHS, UUID);
#else
     // for windows
     createRemoteIpa(&MAP_POST_AND_FILE_PATHS, UUID);

#endif

}


void MainWindow::showAlertWithMsg(QString message){

    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Внимание",
                                                                message,
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
    if(resBtn == QMessageBox::No) {
        logTextBrowser->append("\nФормирование пакетов прекращено.");
        ui->guidLine->clear();
        logTextBrowser->clear();

}

}



QString MainWindow::processViberBackup (QString backupFullPath) {

    QMap <QString, QString> *mapIosPathAndLocalPath =new QMap<QString, QString>();
    QString sqlQuery = "select * from files where (domain LIKE \"%viber%\" and flags=1 AND relativePath LIKE \"Documents%\") OR (relativePath LIKE \"%Contacts.data\")  ";

    getMediaFilesPaths(mapIosPathAndLocalPath, sqlQuery);

    QMap<QString, QString>* filtredMap = getMapForViber(mapIosPathAndLocalPath);

    QString libraryWordForCut = "Documents/";

    if(filtredMap->count() > 0){
        copyFilesToTmpDir(filtredMap, libraryWordForCut.length());
        QString zippedPath = zip(VIBER_DB_FILE);
        if(zippedPath.isEmpty()){
            qDebug() << "faild zip viber db file";
        }
        qDebug() << "Success zip viber db file";
        return zippedPath;

    }

    else
        return "";

}


QMap<QString, QString>* MainWindow::getMapForViber(QMap<QString, QString>* mapIosPathAndLocalPath){

    QMapIterator<QString, QString> iter(*mapIosPathAndLocalPath);

    while (iter.hasNext()) {

        iter.next();
        //Library/Media/77017213945-1409280046@g.us/2/2/220f0a3e-a074-4ade-b2f2-2631be0f5a11.thumb
        QString iosPath  = iter.key();

        //"C:/Users/Admin/AppData/Roaming/Apple Computer/MobileSync/Backup/1b5b94b83e762264209e8482ff965434f0dcd1ab/00/0095d94891ca2b7c2754fe234854b2e34807b57a"
        QString localPath = iter.value();

        if(iosPath.contains("com.viber/database/Contacts.data")){
            mapIosPathAndLocalPath->insert("Documents/Contacts.data",iter.value() );
            mapIosPathAndLocalPath->remove(iter.key());
        }

    }

    return mapIosPathAndLocalPath;

}



QString MainWindow::processWhatsappBackup (QString backupFullPath){

     //move ChatStorage.sqlite path
     logTextBrowser->append("\nИдет Обработка файлов для мессенджера Whatsapp.........");
     logTextBrowser->append("\nИдет копирование базы данных Whatsapp .........");
     QString ChatStorageCopiedPath = copyStorageFile();

     if(ChatStorageCopiedPath.isEmpty()){

         setRESULT_PARSING(RESULT_NO_DB);
         endParseApp(0,QProcess::NormalExit);
         return "";
     }

     // move media files
     logTextBrowser->append("\nКопирование медиа файлов в временную директорию.........");
     QMap <QString, QString> *mapIosPathAndLocalPath =new QMap<QString, QString>();
     QString sqlQuery = "select * from files where domain LIKE \"%AppDomain-net.whatsapp.WhatsApp%\" AND relativePath LIKE \"%Library/Media%\" AND flags = 1";
     getMediaFilesPaths(mapIosPathAndLocalPath, sqlQuery);
     QString libraryWordForCut = "Library/";

     if(mapIosPathAndLocalPath->count() > 0) {
         copyFilesToTmpDir(mapIosPathAndLocalPath, libraryWordForCut.length());


         //---------------check size of all files in backup----------------------------------
         quint64 backupSize = dir_size(getBackupTmpDirFullPath());
         if(backupSize > MAX_BYTE_PERMIT_FOR_BACKUP){
             showAlertWithInfoMsg("Размер бэкапа слишком большой, восстановление не возможно. Попробуйте отключить восстановление видеофайлов");
             setRESULT_PARSING(RESULT_BACKUP_SIZE_UP_LIMIT);
             endParseApp(0,QProcess::NormalExit);
             return "PARSING_BREAKING";
         }

         /*
         if(backupSize > SIZE_OF_BACKUP_VERY_BIG){
             QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Внимание",
                                                                             tr("Внимание! Размер бэкапа Whatsapp очень большой. Восстановление переписки возможно, однако при медленном интернете это займет большой количество времени. Продолжить формирование пакета с восстановлением переписки ?"),
                                                                             QMessageBox::No | QMessageBox::Yes,
                                                                             QMessageBox::No);
             if(resBtn == QMessageBox::No) {
                 logTextBrowser->append("\nФормирование пакетов прекращено.");
                 ui->guidLine->clear();
                  logTextBrowser->clear();
                 clear();
                 return BREAKE_PARSING;
             }


         }
         */



         //zip file for whatsapp
         logTextBrowser->append("\nСоздание архива медиафайлов Whatsapp .........\n");
         zip(WHATSAPP_MEDIA_ZIP_FILENAME);



         return "";

     }

     else
         return "";


}


QString MainWindow::processWechatBackup(QString backupFullPath){

    QMap <QString, QString> *mapIosPathAndLocalPath =new QMap<QString, QString>();
    //QString sqlQuery = "select * from files where domain LIKE \"%AppDomain-net.whatsapp.WhatsApp%\" AND relativePath LIKE \"%Library/Media%\" AND flags = 1";
    //QString sqlQuery = "select * from Files where relativePath  LIKE \"%MM.sqlite\" AND domain = \"AppDomain-com.tencent.xin\"";
    QString sqlQuery  = "select * from Files where domain = \"AppDomain-com.tencent.xin\" "
                        "AND ("
                        "(relativePath  LIKE \"%MM.sqlite\") "
                        "or (relativePath  LIKE \"%WCDB_Contact.sqlite\")"
                        "or (relativePath LIKE \"%Audio%\" AND flags = 1)"
                        " or (relativePath LIKE \"%Video%\"  AND flags = 1) "
                        "or (relativePath LIKE \"%Img%\" AND flags = 1 )"
                        ")";



    getMediaFilesPaths(mapIosPathAndLocalPath, sqlQuery);

    QString libraryWordForCut = "Documents/";

    if(mapIosPathAndLocalPath->count() > 0){
        copyFilesToTmpDir(mapIosPathAndLocalPath, libraryWordForCut.length());

        //---------------check size of all files in backup----------------------------------
        quint64 backupSize = dir_size(getBackupTmpDirFullPath());
        if(backupSize > MAX_BYTE_PERMIT_FOR_BACKUP){
            showAlertWithInfoMsg("Размер бэкапа слишком большой, восстановление не возможно. Попробуйте отключить восстановление видеофайлов");
            setRESULT_PARSING(RESULT_BACKUP_SIZE_UP_LIMIT);
            endParseApp(0,QProcess::NormalExit);
            return "PARSING_BREAKING";
        }

        /*
        if(backupSize > SIZE_OF_BACKUP_VERY_BIG){
            QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Внимание",
                                                                            tr("Внимание! Размер бэкапа Whatsapp очень большой. Восстановление переписки возможно, однако при медленном интернете это займет большой количество времени. Продолжить формирование пакета с восстановлением переписки ?"),
                                                                            QMessageBox::No | QMessageBox::Yes,
                                                                            QMessageBox::No);
            if(resBtn == QMessageBox::No) {
                logTextBrowser->append("\nФормирование пакетов прекращено.");
                ui->guidLine->clear();
                 logTextBrowser->clear();
                clear();
                return "PARSING_BREAKING";
            }


        }
        */

         zip(WECHAT_DB_FILE);

        return "";

    }

    else
        return "";

//select * from Files
//where domain = "AppDomain-com.tencent.xin"
//AND ((relativePath  LIKE "%MM.sqlite")
//or (relativePath LIKE "%Audio%" AND flags = 1)
//or (relativePath LIKE "%Video%"  AND flags = 1)
//or (relativePath LIKE "%Img%" AND flags = 1 ))

}

bool MainWindow::connectDatabase(const QString& database)
{

     db =  QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName(database);

    bool  res = db.open();
     if (!res){
         qDebug() << "database not opened";
         return false;
     }
     else{
         qDebug() << "database sucsses opened";
         logTextBrowser->append("Манифест файл успешно считался");
        // db.close();

     }
     return true;
}


QString MainWindow::copyStorageFile(){

    QString copiedStoragePath = "";

    QSqlQuery query(db);
    QString cmd = "select * from files where relativePath = 'ChatStorage.sqlite'";

    bool success = query.exec(cmd);
    if (!success){
         qDebug() << "faild select";
         return "";
    }

    if(query.next())
    {
         QString hash = query.value(0).toString();
         QString iosFileName = query.value(2).toString();
         currentBackup = QString("%1/%2").arg(pathToAllBackup,ui->backupsListComBox->currentText() );
         QDirIterator dirIter(currentBackup, QStringList() << hash, QDir::Files, QDirIterator::Subdirectories);
         if(dirIter.hasNext()){
             QString localPath = dirIter.next();
             //copy
             QString tempDirPath = getBackupTmpDirFullPath();
             if(tempDirPath.isEmpty()){
                 qDebug() << "faild create tmpDir";
                  return "";
             }
             QString srcFilePAth = localPath;
             QString dstFilePath = QString("%1/%2").arg(tempDirPath,iosFileName );
             QFile file;
             bool isCopiedSuccess =  file.copy(srcFilePAth, dstFilePath);

            if(!isCopiedSuccess){
                qDebug() << "faild copy file from src path: " << srcFilePAth << " toPath: " << dstFilePath;
                 return "";
            }

            else{
                return dstFilePath;
            }
         }

         return "";
    }

    else
        return "";



}


bool MainWindow::getMediaFilesPaths( QMap <QString, QString>* mapIosPathAndLocalPath,  QString sqlIn){
    //1 Get media files paths
    QSqlQuery query(db);
   // QString cmd = "select * from files where domain LIKE \"%AppDomain-net.whatsapp.WhatsApp%\" AND relativePath LIKE \"%Library/Media%\" AND flags = 1";
   QString cmd = sqlIn;

    bool success = query.exec(cmd);
    if (!success){
         qDebug() << "faild select";
         return false;
    }

    QMap <QString, QString> mapHashPath;

    int countRowInDb = 0;
    while(query.next())
    {
        QString hash = query.value(0).toString();
        QString pathInIOS = query.value(2).toString();
        mapHashPath.insert(hash,pathInIOS);
        countRowInDb++;
    }


    currentBackup = QString("%1/%2").arg(pathToAllBackup,ui->backupsListComBox->currentText() );
    QMapIterator<QString, QString> iter(mapHashPath);
    qint64 countFind = 0;
    while (iter.hasNext()) {
        iter.next();
        qDebug() << iter.key() << ": " << iter.value() << endl;

        if(ui->noRestoreCheckBox->isChecked()){
            if(iter.value().contains("mp4")){
                continue;
            }
        }

        QDirIterator dirIter(currentBackup, QStringList() << iter.key(), QDir::Files, QDirIterator::Subdirectories);
        while(dirIter.hasNext()){
            mapIosPathAndLocalPath->insert(iter.value(),dirIter.next() );
        }

        qDebug() << "count of find loop:" << countFind;
        qDebug() << "current size of finded map is:" << mapIosPathAndLocalPath->count();
        countFind++;

        //for test
#ifdef TEST
        if(countFind > 5){
            break;
        }
#endif
    }

    qDebug() << "Finished Count of finded files is:" << mapIosPathAndLocalPath->count();
    return true;
}

bool MainWindow::copyFilesToTmpDir (QMap <QString, QString>* mapIosPathAndLocalPath, int lenghForCut){

    // get tmp dir

    QString tempDirPath = getBackupTmpDirFullPath();
    if(tempDirPath.isEmpty()){
        qDebug() << "faild create tmpDir";
        return false;
    }

    QMapIterator<QString, QString> iter(*mapIosPathAndLocalPath);

    while (iter.hasNext()) {

        iter.next();
        //Library/Media/77017213945-1409280046@g.us/2/2/220f0a3e-a074-4ade-b2f2-2631be0f5a11.thumb
        QString iosPath  = iter.key();

        //"C:/Users/Admin/AppData/Roaming/Apple Computer/MobileSync/Backup/1b5b94b83e762264209e8482ff965434f0dcd1ab/00/0095d94891ca2b7c2754fe234854b2e34807b57a"
        QString localPath = iter.value();

        qDebug() << iosPath << ":" << localPath;

        //cut from iosPath Library/
        QString fileName = QFileInfo(iosPath).fileName();
        iosPath = iosPath.remove(0,lenghForCut);
        iosPath = iosPath.replace(fileName, "");

        QString pathWithAllDirs = QString("%1/%2").arg(tempDirPath,iosPath );

        QDir dirForMedia(pathWithAllDirs);

        if(!dirForMedia.exists()){
            bool succes = dirForMedia.mkpath(pathWithAllDirs);
            if(!succes){
                qDebug() << "faild to create folder with path:" << pathWithAllDirs;
            }
        }

        //copy
        QString srcFilePAth = localPath;
        QString dstFilePath = QString("%1/%2").arg(pathWithAllDirs,fileName );

        QFile file;

       bool isCopiedSuccess =  file.copy(srcFilePAth, dstFilePath);

       if(!isCopiedSuccess){
           qDebug() << "faild copy file from src path: " << srcFilePAth << " toPath: " << dstFilePath;
       }

    }

    return true;

}

QString MainWindow::zip(QString zipFileName){

    QString zipPath = "";

#if (defined (Q_OS_MAC32) || defined (Q_OS_MAC64))
     zipPath = zipForMac(zipFileName);
#else
    zipPath = zipForWin(zipFileName);
#endif

    return zipPath;

}

QString MainWindow::zipForMac(QString zipFileName)
{
    QProcess* zipProc = new QProcess(this);

    //connect
    QObject::connect(zipProc, SIGNAL(finished(int,QProcess::ExitStatus)),
                         this, SLOT(endParseApp(int, QProcess::ExitStatus)));


    QString cmd = "/usr/bin/zip";
    QString zippedFileName = QString("%1/%2").arg(getBackupTmpDirFullPath(),zipFileName);
    QStringList argZip;
    argZip << "-r" << zippedFileName;

    //set list of dir
    QDir dir(getBackupTmpDirFullPath());

    QStringList list = dir.entryList();

    foreach (QString dirOrFileName, list) {
        if(dirOrFileName == "." || dirOrFileName == ".."){
            continue;
        }

        argZip << dirOrFileName;
    }

    setCURRENT_ZIPPED_FILE_PATH(zippedFileName);
    setRESULT_PARSING(RESULT_ZIP_IS_SUCCESS);
    zipProc->setWorkingDirectory(getBackupTmpDirFullPath());
    zipProc->start(cmd, argZip);

   // if (!zipProc->waitForFinished())
    //    return "";



    return zippedFileName;



}

QString MainWindow::zipForWin(QString zipFileName)
{

    //"%ProgamFiles%\WinRAR\Rar.exe" a -ep1 -r "Name of ZIP file with path" "%UserProfile%\Desktop\someFolder"
   // rar a backup @backup.lst

    QProcess* zipProc = new QProcess(this);
    QString cmd = getWinRarExePath();
    if (cmd.isEmpty()){
        qDebug() << "faild get rar.exe path";
        return "";
    }

    QString zippedFileName = QString("%1/%2").arg(getBackupTmpDirFullPath(),zipFileName);
//"C:\Program Files\WinRAR\WinRAR.exe" a -afzip -ep1 C:/Users/vohulg/AppData/Local/Temp/e9bdd3562cdccb727e7d41a7051f2b2880388aa8/wmedia.zip @C:/Users/vohulg/AppData/Local/Temp/e9bdd3562cdccb727e7d41a7051f2b2880388aa8.lst
    QStringList argZip;
    argZip << "a" << "-afzip" << "-ep1" << zippedFileName << QString("@%1").arg(getLstFile());
    zipProc->start(cmd, argZip);

    if (!zipProc->waitForFinished())
        return "";

    QByteArray zipResult = zipProc->readAll();

    qDebug() << "zip result:" << zipResult;

    return zippedFileName;


}

QString MainWindow::getLstFile(){

    QString lstFilePath =  QString("%1/%2.lst").arg(QDir::tempPath(),UUID);
    QFile fileLst(lstFilePath);
    if (!fileLst.open(QIODevice::WriteOnly)){
        return "";
    }
    QTextStream out(&fileLst);
       // out << "The magic number is: " << 49 << "\n";


    QDir backupDir(getBackupTmpDirFullPath());
    QStringList list =  backupDir.entryList();

    foreach(QString dirName,list){
        if(dirName == "." || dirName == ".."){
            continue;
        }

        //write to lst file
        QString fullPath = QString("%1/%2").arg(getBackupTmpDirFullPath(), dirName);
        if(fullPath.contains(WHATSAPP_DB_FILENAME)){
            continue;
        }
        out << fullPath << "\n";

    }

    fileLst.close();
    return lstFilePath;




}

bool MainWindow::clear(){

    QString lstFile = QString("%1/%2.lst").arg(QDir::tempPath(), UUID);
    if (QFile::exists(lstFile)){
        QFile::remove(lstFile);
    }

    QString tmpDirForUUID = QString("%1/%2").arg(QDir::tempPath(), UUID);
    QDir dir;
    if (dir.exists(tmpDirForUUID)){
        QDir dirForRemove(tmpDirForUUID);
        dirForRemove.removeRecursively();
    }

    QString tmpDirForUUIDresult = QString("%1/%2-result").arg(QDir::tempPath(), UUID);
    if (dir.exists(tmpDirForUUIDresult)){
        QDir dirForRemove(tmpDirForUUIDresult);
        dirForRemove.removeRecursively();
    }

    return true;
}

QString  MainWindow::getWinRarExePath(){

    //QString winrarExe = "C:\\Program Files\\WinRAR\\Rar.exe";
QString winrarExe = "C:\\Program Files\\WinRAR\\WinRAR.exe";

    QFile file(winrarExe);

    if(file.exists()){

        return winrarExe;
    }
    else{
        return "";
    }

}

QString MainWindow::getBackupTmpDirFullPath (){

    QString tempDirPath = QString("%1/%2").arg(QDir::tempPath(), UUID);
    QDir tmpDir(tempDirPath);

    if(!tmpDir.exists()){
        bool isSuccess = tmpDir.mkdir(tempDirPath);
        if(!isSuccess){
            qDebug() << "faild create temp folder at path" << tempDirPath;
           return "";
        }

    }

    return tempDirPath;

}

QString MainWindow::getNameFromFullPath(QString fullPath){

    QFile file(fullPath);
    QString str = file.fileName();
    QStringList parts = str.split("/");
    QString lastSection = parts.at(parts.size()-1);
    return lastSection;

}

QByteArray MainWindow::getAppList(){

    QStringList appList;

    if(ui->whatsappAppcheckBox->isChecked()){
        appList << "w";
    }

    if(ui->TelegramAppCheckBox->isChecked()){
        appList << "t";
    }

    if(ui->WechatAppCheckBox->isChecked()){
        appList << "c";
    }

    if(ui->ViberAppCheckBox->isChecked()){
        appList << "v";
    }


     QByteArray appListBuf = NULL;
    if(appList.count() > 0){
        appListBuf =  appList.join(",").toUtf8();
    }

   return appListBuf;
}

quint64 MainWindow::dir_size(const QString &str)
{
    quint64 sizex = 0;
       QFileInfo str_info(str);
       if (str_info.isDir())
       {
           QDir dir(str);
           QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
           for (int i = 0; i < list.size(); ++i)
           {
               QFileInfo fileInfo = list.at(i);
               if(fileInfo.isDir())
               {
                       sizex += dir_size(fileInfo.absoluteFilePath());
               }
               else
                   sizex += fileInfo.size();

           }
       }
       return sizex;
}

bool MainWindow::sendAllBackup (QMap <QString, QString>* mapPostAndFilePath, QString uuid) {

    QNetworkAccessManager *manager =  new QNetworkAccessManager(this);

    QByteArray  paramTextPlain="text/plain";
    QByteArray  paramOctetStream="application/octet-stream";

    QByteArray paramUuidName="uuid" ,paramUuidValue=uuid.toUtf8();
    QByteArray paramGuidName="guid" ,paramGuidValue=GUID_BYTEARR;
    QByteArray paramNameUrl="url" ,paramUrlValue=URL_BYTEARR;
     QByteArray paramNameApplist="applist" ,paramAppListValue=getAppList();

     if(paramAppListValue.isNull()){

         logTextBrowser->append("Приложения либо не выбраны либо содержат большой бэкап");
         return false;
     }

    //задаем разделитель
    QByteArray postData,boundary="-----------------------1BEF0A57BE110FD467A";

    // параметр uuid
    postData.append("--"+boundary+"\r\n");//разделитель
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(paramUuidName);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(paramUuidValue);
    postData.append("\r\n");

    // параметр guid
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(paramGuidName);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(paramGuidValue);
    postData.append("\r\n");

    // параметр url
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(paramNameUrl);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(paramUrlValue);
    postData.append("\r\n");

    // параметр applist
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(paramNameApplist);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(paramAppListValue);
    postData.append("\r\n");


    //attach files
    QMapIterator<QString, QString> iter(*mapPostAndFilePath);
    while (iter.hasNext()) {

        iter.next();
        QString postValue  = iter.key();
        QString filePath = iter.value();
        QString fileName = getNameFromFullPath(filePath);

        QFile file(filePath);
        if (!file.open(QIODevice::ReadWrite)){
            logTextBrowser->append(QString(" Не найден файл с архивом: %1 ").arg(filePath));
            continue;
        }

        QByteArray paramAttachName=postValue.toUtf8(), paramAttachFileName=fileName.toUtf8();
        QByteArray paramAttachData=file.readAll();


        //параметр приаттаченный файл
        postData.append("--"+boundary+"\r\n");//разделитель
        //имя параметра
        postData.append("Content-Disposition: form-data; name=\"");
        postData.append(paramAttachName);
        //имя файла
        postData.append("\"; filename=\"");
        postData.append(paramAttachFileName);
        postData.append("\"\r\n");
        //тип содержимого файла
        postData.append("Content-Type: "+paramOctetStream+"\r\n\r\n");
        //данные
        postData.append(paramAttachData);
        postData.append("\r\n");
    }


    //"хвост" запроса
    postData.append("--"+boundary+"--\r\n");

    QNetworkRequest request(QUrl("http://88.204.154.151/in.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "multipart/form-data; boundary="+boundary);
    request.setHeader(QNetworkRequest::ContentLengthHeader,
        QByteArray::number(postData.length()));

    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(sendReportToServerReply(QNetworkReply*)));
     //connect(manager, SIGNAL(),this, SLOT();

    logTextBrowser->append("Идет отправка архива на сервер......");
    QNetworkReply *reply=manager->post(request,postData);
    return true;
}

bool MainWindow::sendZip (QString zipFullPath, QString uuid){

    QString fileName = getNameFromFullPath(zipFullPath);

    QFile file(zipFullPath);
    if (!file.open(QIODevice::ReadWrite)){
        logTextBrowser->append(QString(" Не найден файл с медиа архивом: %1 ").arg(zipFullPath));
        return false;
    }

    QString dbFileNameFullPath = zipFullPath;
    QString dbFileName = WHATSAPP_DB_FILENAME;
    dbFileNameFullPath.replace(WHATSAPP_MEDIA_ZIP_FILENAME, WHATSAPP_DB_FILENAME);

    QFile dbFileFd(dbFileNameFullPath);
    if (!dbFileFd.open(QIODevice::ReadWrite)){
        logTextBrowser->append(QString(" Не найден файл с  архивом базы данных : %1 ").arg(dbFileNameFullPath));
        return false;
    }

    QNetworkAccessManager *manager =  new QNetworkAccessManager(this);;
    //параметр 1 - uuid, параметр 2 - файл параметр 3 - guid
    QByteArray param1Name="uuid" ,param1Value=uuid.toUtf8();
    QByteArray  param1ContentType="text/plain";

    QByteArray param3Name="guid" ,param3Value=GUID_BYTEARR;
    QByteArray  param3ContentType="text/plain";

    QByteArray paramNameUrl="url" ,paramUrlValue=URL_BYTEARR;
    QByteArray  paramUrlContentType="text/plain";

    QByteArray param2Name=WHATSAPP_MEDIA_ZIP_POST_NAME.toUtf8(), param2FileName=fileName.toUtf8();
    QByteArray  param2ContentType="application/octet-stream";
    QByteArray param2Data=file.readAll();

    QByteArray param4Name=WHATSAPP_DB_POST_NAME.toUtf8(), param4FileName=dbFileName.toUtf8();
    QByteArray  param4ContentType="application/octet-stream";
    QByteArray param4Data=dbFileFd.readAll();

    //задаем разделитель
    QByteArray postData,boundary="-----------------------1BEF0A57BE110FD467A";

    // параметр uuid
    postData.append("--"+boundary+"\r\n");//разделитель
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(param1Name);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(param1Value);
    postData.append("\r\n");

    // параметр guid
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(param3Name);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(param3Value);
    postData.append("\r\n");

    // параметр url
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(paramNameUrl);
    postData.append("\"\r\n\r\n");
    //значение параметра
    postData.append(paramUrlValue);
    postData.append("\r\n");

    //параметр 2 - файл
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(param2Name);
    //имя файла
    postData.append("\"; filename=\"");
    postData.append(param2FileName);
    postData.append("\"\r\n");
    //тип содержимого файла
    postData.append("Content-Type: "+param2ContentType+"\r\n\r\n");
    //данные
    postData.append(param2Data);
    postData.append("\r\n");

    //параметр 4 - файл базы данных
    postData.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData.append("Content-Disposition: form-data; name=\"");
    postData.append(param4Name);
    //имя файла
    postData.append("\"; filename=\"");
    postData.append(param4FileName);
    postData.append("\"\r\n");
    //тип содержимого файла
    postData.append("Content-Type: "+param4ContentType+"\r\n\r\n");
    //данные
    postData.append(param4Data);
    postData.append("\r\n");


    //"хвост" запроса
    postData.append("--"+boundary+"--\r\n");

    QNetworkRequest request(QUrl("http://88.204.154.151/in.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "multipart/form-data; boundary="+boundary);
    request.setHeader(QNetworkRequest::ContentLengthHeader,
        QByteArray::number(postData.length()));

    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(sendReportToServerReply(QNetworkReply*)));
     //connect(manager, SIGNAL(),this, SLOT();

    logTextBrowser->append("Идет отправка архива на сервер......");
    QNetworkReply *reply=manager->post(request,postData);


    return true;
}

void MainWindow::sendReportToServerReply(QNetworkReply* reply){

     ui->startBtn->setEnabled(true);

     QByteArray replyInByte = reply->readAll();
     qint64 size = replyInByte.size();

      if(replyInByte.size() < SIZE_UNIQ_URL || replyInByte.contains("ERROR")){
          logTextBrowser->append("Ошибка в передаче архива на сервер:");
          logTextBrowser->append(QString::fromLatin1(replyInByte));
          return;
     }

     QString replyStr = QString::fromLatin1(replyInByte);
     QString log = QString("\nДля установки программ на телефон сначала удалите оригинальные приложения затем откройте браузер на телефоне и перейдите по ссылки %1/%2 \n").arg(INSTALL_URL,replyStr);
     logTextBrowser->append(log);

     QString url = QString("%1/%2").arg(INSTALL_URL,replyStr);
     instructionForm.setUrl(url);
     instructionForm.show();

     // сохранение UUID в файл на рабочем столе и отправка на почту
     QString fullPath = QString("%1/Desktop/%2.log").arg(QDir::homePath(), UUID);
     QDateTime currentDT =  QDateTime::currentDateTime();
     QString dateTimeStr = currentDT.toString("dd.MM.yyyy_hh.mm.ss");
     QString pathWithDate = QString("%1_%2").arg(fullPath,dateTimeStr);
     bool successSave = saveLog(pathWithDate);

     if (successSave) {
         logTextBrowser->append(QString("\n\n Логи сохранены в файле %1 \n\n ").arg(pathWithDate));
     }
     else {
         logTextBrowser->append(QString("\n\n Ошибка при сохранении логов в файл по пути %1 \n\n").arg(pathWithDate));
     }



 }

void MainWindow::sendPost(){

    //QUrl serviceUrl = QUrl("http://myserver/myservice.asmx");
     QNetworkRequest request(QUrl("http://88.204.154.151/in.php"));
     QByteArray postData;
     postData.append("uuid=925dsfh90325793fdsif0932878fdoisf");

      /*
      Setup the post data somehow
      I want to transmit:
      param1=string,
      param2=string
      */

       // Call the webservice
       QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
       connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sendReportToServerReply(QNetworkReply*)));
       networkManager->post(request, postData);
}

void  MainWindow::sendMultiPart(){

   // QString zipFile = "C:\\Users\\vohulg\\AppData\\Local\\Temp\\6f3f394f07f8edd922b701fc3db69ede00bb5360\\whatsapp.zip";
    QString zipFile = "C:\\Users\\vohulg\\AppData\\Local\\Temp\\6f3f394f07f8edd922b701fc3db69ede00bb5360\\Samples.cpp";


    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"wzipfile\"; filename=\"sample\""));/* version.tkt is the name on my Disk of the file that I want to upload */

        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uuid\""));
        textPart.setBody("92874fhdsfh932744545454rwyri");/* toto is the name I give to my file in the server */

        QFile *file = new QFile(zipFile);
        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

        multiPart->append(textPart);
        multiPart->append(imagePart);

       QNetworkRequest request(QUrl("http://88.204.154.151/in.php"));

        QNetworkAccessManager *networkManager= new QNetworkAccessManager;
        networkManager->post(request, multiPart);
       // multiPart->setParent(reply); // delete the multiPart with the reply


}


bool MainWindow::saveLog(QString fileFullPath){

    QFile fileLog(fileFullPath);
    if (!fileLog.open(QIODevice::WriteOnly)){
        return false;
    }
    QTextStream out(&fileLog);
    out << "UUID:" << UUID << "\n";

    //write log info
    QTextDocument *doc = logTextBrowser->document();
    QString logText = doc->toPlainText();

    out << "LOG: \n" << logText.toUtf8();

    return true;



}

//set guid from file
void MainWindow::on_chooseFileBtn_clicked()
{
     ui->startBtn->setEnabled(false);
     GUID_BYTEARR = NULL;
     URL_BYTEARR = NULL;


        QString filter = "Any files (*)";
       QString* selecFilter = &filter;
       QString fileWithGuid = QFileDialog::getOpenFileName(this, tr("Open image file"), tr("/"), filter, selecFilter, QFileDialog::DontConfirmOverwrite );

       QFile fileGuid(fileWithGuid);
       if (!fileGuid.open(QIODevice::ReadOnly)){
           QMessageBox::critical(this, "Error", "File not exist");
           return ;
       }

       setGUID_FILE_PATH(fileWithGuid);

       ALIAS_BYTEARR = fileGuid.readLine().trimmed();// read alias, not used

        //get url
       URL_BYTEARR = fileGuid.readLine().trimmed();
       if(URL_BYTEARR.length() < 5 || !URL_BYTEARR.contains("http")){
           saveLog("Url data not match");
           QMessageBox::critical(this, "Error", "Url data not match");
           return ;
       }

       //get guid
       #define GUID_LEN 36
       GUID_BYTEARR = fileGuid.readLine().trimmed();
       if(GUID_BYTEARR.length() != GUID_LEN){
           saveLog("Guid data not match");
           QMessageBox::critical(this, "Error", "Guid data not match");
           return ;
       }

       logTextBrowser->append("Guid успешно загружен!");
       //saveLog("2.Guid успешно загружен!");
       logTextBrowser->append("3. Выберите идентификатор бэкапа и нажмите старт");
       ui->guidLine->setText(ALIAS_BYTEARR);
       ui->startBtn->setEnabled(true);\

}

void MainWindow::on_action_triggered()
{
    instructionForm.show();
}

void MainWindow::on_btnUpdate_clicked()
{
    // download script.zip and change
}

void MainWindow::on_actionOpenTasksDir_triggered()
{


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 QString("%1/WORK/tasks").arg(QDir::homePath()),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

}

void MainWindow::on_actionOpenCurrentTaskDir_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 getCurrentWorkDir(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

}

void MainWindow::on_btnOpenReadyIpaDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Packets for install"),
                                                 QString("%1/scripts/ipa").arg(getCurrentWorkDir()),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
}
