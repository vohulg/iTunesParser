#ifndef VGPARSERTHREAD_H
#define VGPARSERTHREAD_H

#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QNetworkReply>

#define SIZE_UNIQ_URL 8

class VGParserThread : public QThread
{
    Q_OBJECT

public:
   // VGParserThread();
    void setValues(QString manifestpath, QString UUID, QSqlDatabase db, QString currentBackup,  QByteArray GuidByteArr,  QByteArray URLByteArr);

    bool process(QString backupFullPath);
private:
    QString manifestpath;
     QString UUID; //use for name tmpFolder
     QSqlDatabase db;
     QString currentBackup;
     QByteArray GuidByteArr;
     QByteArray URLByteArr;


     bool connectDatabase(const QString &database);
     bool copyStorageFile();
     bool getMediaFilesPaths(QMap<QString, QString> *mapIosPathAndLocalPath);
     bool copyFilesToTmpDir(QMap<QString, QString> *mapIosPathAndLocalPath);
     QString zip(QString zipFileName);
     QString getLstFile();
     bool clear();
     QString getWinRarExePath();
     QString getBackupTmpDirFullPath();
     QString getNameFromFullPath(QString fullPath);
     bool sendZip(QString zipFullPath, QString uuid);
     void sendReportToServerReply(QNetworkReply *reply);
     void sendPost();
     void sendMultiPart();

     void testProcess();
     void run();

signals:
    void changeLog( const QString & log);
    void saveLogSig( const QString & pathWithDate);


};

#endif // VGPARSERTHREAD_H
