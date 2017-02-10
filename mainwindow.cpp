#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pathToAllBackup = "C:\\Users\\Admin\\AppData\\Roaming\\Apple Computer\\MobileSync\\Backup";


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBtn_clicked()
{
 //ui->progressBar->setRange(0,100);
 //ui->progressBar->setValue(100);
 //ui->progressBar->setRange(0,0);

    //1 get list of contents of folder
    QDir backupDir(pathToAllBackup);
   QStringList list =  backupDir.entryList();

   foreach(QString dirName,list){
       if(dirName == "." || dirName == ".."){
           list.removeOne(dirName);
           continue;
       }
   }



   qint8 a = 0;




}
