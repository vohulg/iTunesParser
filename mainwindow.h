#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>
#include "quazip.h"
#include "quazipfile.h"

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

private:
    Ui::MainWindow *ui;
    QString pathToAllBackup;
    QString currentBackup;
    void runTest();
    void setBackUpRootPath();
    void showAllBackups();
    void parseDb(QString backupFullPath);
    bool connectDatabase(const QString& database);

    QSqlDatabase db;
    bool copyFilesToTmpDir(QMap<QString, QString> mapIosPathAndLocalPath);
    bool getMediaFilesPAths(QMap<QString, QString> mapIosPathAndLocalPath);
};

#endif // MAINWINDOW_H
