#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "QDebug"
#include "QFileDialog"
#include "QMessageBox"

#define TEST

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   setBackUpRootPath();
   showAllBackups();
   logTextBrowser = ui->logTextBrowser;
   logTextBrowser->append("1. Загрузите файс с номером задания");
   logTextBrowser->append("2. Выберите идентификатор бэкапа и нажмите старт");
   ui->startBtn->setEnabled(false);
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

void MainWindow::saveLogSlot(const QString & pathWithDate)
{

    bool successSave = saveLog(pathWithDate);

    if (successSave) {
       logTextBrowser->append(QString("\n\n UUID устройства и логи сохранены в файле %1 \n\n ").arg(pathWithDate));
    }
    else {
       logTextBrowser->append(QString("\n\n Ошибка при сохранении логов в файл по пути %1 \n\n").arg(pathWithDate));
    }


}

void MainWindow::setBackUpRootPath(){

    pathToAllBackup = QString("%1/AppData/Roaming/Apple Computer/MobileSync/Backup").arg(QDir::homePath());

}


void MainWindow::on_startBtn_clicked()
{

    QString manifestPath = QString("%1/%2/%3").arg(pathToAllBackup,ui->backupsListComBox->currentText(), "Manifest.db" );

    UUID = ui->backupsListComBox->currentText();
    currentBackup = QString("%1/%2").arg(pathToAllBackup,ui->backupsListComBox->currentText() );

    parserThread = new VGParserThread();

    QObject::connect(parserThread, SIGNAL(changeLog(const QString &)), SLOT(showLog(const QString &)), Qt::QueuedConnection);
    QObject::connect(parserThread, SIGNAL(saveLogSig(const QString &)), SLOT(saveLogSlot(const QString &)), Qt::QueuedConnection);


    parserThread->setValues(manifestPath, UUID, db, currentBackup, GuidByteArr, URLByteArr);
    parserThread->start();

    //process(manifestPath);




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

       //get guid
       #define GUID_LEN 36
       QByteArray GuidByteArr = fileGuid.readLine().trimmed();
       if(GuidByteArr.length() != GUID_LEN){
           QMessageBox::critical(this, "Error", "Guid data not match");
           return ;
       }

       //get url
       QByteArray URLByteArray = fileGuid.readLine().trimmed();
       if(URLByteArray.length() < 5 || !URLByteArray.contains("http")){
           QMessageBox::critical(this, "Error", "Url data not match");
           return ;

       }

       ui->startBtn->setEnabled(true);\

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

void MainWindow::showLog(const QString &log)
{
     logTextBrowser->append(log);
}
