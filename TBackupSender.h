#ifndef TBACKUPSENDER_H
#define TBACKUPSENDER_H

#include <QObject>
#include "TConstants.h"
#include "QComboBox"
#include "QPushButton"
#include <QTextBrowser>
#include <QCheckBox>
#include <QProcess>

class TBackupSender : public QObject
{
    Q_OBJECT
public:
    explicit TBackupSender(QObject *parent = 0);

    QComboBox* comboBoxTasks;
    QPushButton* btnSendBackup;
    QTextBrowser* logSendBAckup;
    QCheckBox* whatsappCheckBox;
    QCheckBox* wechatCheckBox;
     QCheckBox* telegramCheckBox;

     QString getCurrentUrl() const;
     void setCurrentUrl(const QString &value);

     QString getCurrentGuid() const;
     void setCurrentGuid(const QString &value);

signals:
     void finish_backup_sending(int finishCode);

public slots:
     void tabBarClickedSlot(int tabId);
private slots:
    void showAllTasks();
    void btnSendBackupClickSlot(bool);
    QStringList getTargetAppList();
    bool setUrlAndGuid();
    void finishSendBackup(int, QProcess::ExitStatus);
    void runSendProc(QStringList targetApps);
    void endSendBackUp();
    void clean();

private:
    QStringList targetAppsList;
    QString currentUrl;
    QString currentGuid;
};

#endif // TBACKUPSENDER_H
