#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include "vgparserthread.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void on_startBtn_clicked();
     void on_chooseFileBtn_clicked();
     bool saveLog(QString fileFullPath);
     void showLog(const QString & log);
     void setBackUpRootPath();
     void showAllBackups();
     void saveLogSlot( const QString & pathWithDate);
private:
    VGParserThread* parserThread;

private:
    Ui::MainWindow *ui;
    QString pathToAllBackup;
    QString currentBackup;
    QString UUID; //use for name tmpFolder
    QTextBrowser* logTextBrowser;
    QSqlDatabase db;

    QByteArray GuidByteArr;
    QByteArray URLByteArr;


/*
    void runTest();

    bool process(QString backupFullPath);
    bool connectDatabase(const QString& database);    
    bool copyFilesToTmpDir(QMap<QString, QString>* mapIosPathAndLocalPath);
    bool getMediaFilesPaths(QMap<QString, QString>* mapIosPathAndLocalPath);
    bool copyStorageFile();
    QString getBackupTmpDirFullPath();
    QString zip(QString zipFileName);
    QString getWinRarExePath();
    QString getLstFile();
    bool clear();
    bool sendZip(QString zipFullPath, QString uuid);
    QString getNameFromFullPath(QString fullPath);
    void sendPost();
    void sendMultiPart();

    void sendReportToServerReply(QNetworkReply* reply);
    */


};

#endif // MAINWINDOW_H
