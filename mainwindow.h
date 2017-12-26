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

#define SIZE_UNIQ_URL 6

#define WHATSAPP_IDENTITY 0
#define WECHAT_IDENTITY 1
#define TELEGRAM_IDENTITY 2
#define VIBER_IDENTITY 3

#define UUID_LENTH 40



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

    void on_action_triggered();

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

    QString processWechatBackup(QString backupFullPath);
    QString processWhatsappBackup (QString backupFullPath);
    QString processViberBackup (QString backupFullPath);
    void showAlertWithMsg(QString message);

    QSqlDatabase db;
    bool copyFilesToTmpDir(QMap<QString, QString>* mapIosPathAndLocalPath, int lenghForCut);
    bool getMediaFilesPaths(QMap<QString, QString>* mapIosPathAndLocalPath, QString sql);

    QMap<QString, QString>* getMapForViber(QMap<QString, QString>* mapIosPathAndLocalPath);

    QString copyStorageFile();
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

    bool sendAllBackup (QMap <QString, QString>* mapPostAndFilePath, QString uuid);
    QByteArray getAppList();
    quint64 dir_size(const QString & str);
    void showAlertWithInfoMsg(QString message);

    QString getBackupTmpDirFullPath_ForResult();
    void moveBackupsToResultFolder();

    QString ALERT_STR;
    qint64 MAX_BYTE_PERMIT_FOR_BACKUP;
    qint64 SIZE_OF_BACKUP_VERY_BIG;

    QByteArray GuidByteArr;
    QByteArray URLByteArr;

    QString WHATSAPP_DB_FILENAME;
    QString WHATSAPP_MEDIA_ZIP_FILENAME;
    QString WHATSAPP_MEDIA_ZIP_POST_NAME ;
    QString WHATSAPP_DB_POST_NAME ;

     QString WECHAT_DB_FILE ;
      QString WECHAT_POST_NAME ;

      QString VIBER_DB_FILE ;
       QString VIBER_POST_NAME ;

     QString IPA_BUILDER_MAC_SERVER_IP ;
     QString IPA_BUILDER_MAC_SERVER_URL;

     QString INSTALL_URL;


};

#endif // MAINWINDOW_H
