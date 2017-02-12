#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "QDebug"

#define TEST

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   setBackUpRootPath();
   showAllBackups();
  // on_startBtn_clicked();

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
    ui->progressBar->setRange(0,0);


    QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), "Manifest.db" );

    //start time
    qint64 startTime =  QDateTime::currentMSecsSinceEpoch();
    parseDb(manifestPath);
    qint64 endTime =  QDateTime::currentMSecsSinceEpoch();

    qDebug() << "Parsing time is:" << (endTime - startTime ) << "millisecond";
    //end time

    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(100);

}

void MainWindow::parseDb(QString backupFullPath){

    qDebug() << "backupFullPath:" << backupFullPath;
    connectDatabase(backupFullPath);

    //1 Select to database
    QSqlQuery query(db);
    QString cmd = "select * from files where domain LIKE \"%AppDomain-net.whatsapp.WhatsApp%\" AND relativePath LIKE \"%Library/Media%\" AND flags = 1";

    bool success = query.exec(cmd);
    if (!success){

         qDebug() << "faild select";
         return;
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

    QMap <QString, QString> mapIosPathAndLocalPath;
    currentBackup = QString("%1/%2").arg(pathToAllBackup,ui->backupsListComBox->currentText() );
    QMapIterator<QString, QString> iter(mapHashPath);
    qint64 countFind = 0;
    while (iter.hasNext()) {
        iter.next();
        qDebug() << iter.key() << ": " << iter.value() << endl;
        QDirIterator dirIter(currentBackup, QStringList() << iter.key(), QDir::Files, QDirIterator::Subdirectories);
        while(dirIter.hasNext()){
            mapIosPathAndLocalPath.insert(iter.value(),dirIter.next() );
        }

        qDebug() << "count of find loop:" << countFind;
        qDebug() << "current size of finded map is:" << mapIosPathAndLocalPath.count();
        countFind++;

        //for test
#ifdef TEST
        if(countFind > 5){
            break;
        }
#endif
    }

    qDebug() << "Finished Count of finded files is:" << mapIosPathAndLocalPath.count();

    copyFilesToTmpDir(mapIosPathAndLocalPath);

}

bool MainWindow::copyFilesToTmpDir (QMap <QString, QString> mapIosPathAndLocalPath){

    // create tmp dir

    QString tempDirPath = QString("%1/vohulg").arg(QDir::tempPath());
     QDir tmpDir(tempDirPath);

    if(!tmpDir.exists()){
        bool isSuccess = tmpDir.mkdir(tempDirPath);
        if(!isSuccess){
            qDebug() << "faild create temp folder at path" << tempDirPath;
           return false;
        }

    }





    QMapIterator<QString, QString> iter(mapIosPathAndLocalPath);
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
        QString dstFilePath = QString("%1/%2").arg(pathWithAllDirs,fileName );

        QFile file;

       bool isCopiedSuccess =  file.copy(srcFilePAth, dstFilePath);

       if(!isCopiedSuccess){
           qDebug() << "faild copy file from src path: " << srcFilePAth << " toPath: " << dstFilePath;
       }

    }

    return true;

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
        // db.close();

     }
     return true;
}
