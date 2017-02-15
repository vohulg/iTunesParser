#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>
#include <QNetworkAccessManager>
#include <QNetworkRequest>


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

private:
    Ui::MainWindow *ui;
    QString pathToAllBackup;
    QString currentBackup;
    QString UUID; //use for name tmpFolder
    void runTest();
    void setBackUpRootPath();
    void showAllBackups();
    bool parseDb(QString backupFullPath);
    bool connectDatabase(const QString& database);

    QSqlDatabase db;
    bool copyFilesToTmpDir(QMap<QString, QString>* mapIosPathAndLocalPath);
    bool getMediaFilesPaths(QMap<QString, QString>* mapIosPathAndLocalPath);
    bool copyStorageFile();
    QString getTmpDirFullPath();
    QString zip();
    QString getWinRarExePath();
    QString getListFilePathFileForZip();
    bool clear();
    bool sendZip(QString zipFullPath, QString uuid);
    QString getNameFromFullPath(QString fullPath);
};

#endif // MAINWINDOW_H
