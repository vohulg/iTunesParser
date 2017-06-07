#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QTextBrowser>

#include "instruction.h"

#define SIZE_UNIQ_URL 8


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
    void sendReportToServerReply(QNetworkReply* reply);

    //void on_pushButton_clicked();

    void on_chooseFileBtn_clicked();

private:
    Ui::MainWindow *ui;
    Instruction instructionForm;
    QString pathToAllBackup;
    QString currentBackup;
    QString UUID; //use for name tmpFolder
    QTextBrowser* logTextBrowser;

    void runTest();
    void setBackUpRootPath();
    void showAllBackups();
    bool process(QString backupFullPath);
    bool connectDatabase(const QString& database);

    QSqlDatabase db;
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
    bool saveLog(QString fileFullPath);

    QByteArray GuidByteArr;
    QByteArray URLByteArr;

    QString WHATSAPP_DB_FILENAME;
    QString WHATSAPP_MEDIA_ZIP_FILENAME;
    QString WHATSAPP_MEDIA_ZIP_POST_NAME ;
    QString WHATSAPP_DB_POST_NAME ;

     QString IPA_BUILDER_MAC_SERVER_IP ;
};

#endif // MAINWINDOW_H
