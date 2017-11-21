/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *actionOpenTasksDir;
    QAction *actionOpenCurrentTaskDir;
    QWidget *centralWidget;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tabInstaller;
    QGroupBox *groupBox;
    QCheckBox *whatsappAppcheckBox;
    QCheckBox *TelegramAppCheckBox;
    QCheckBox *WechatAppCheckBox;
    QCheckBox *ViberAppCheckBox;
    QGroupBox *groupBox_2;
    QLineEdit *guidLine;
    QPushButton *chooseFileBtn;
    QGroupBox *groupBox_3;
    QComboBox *backupsListComBox;
    QCheckBox *noRestoreCheckBox;
    QPushButton *startBtn;
    QLabel *label_2;
    QTextBrowser *logTextBrowser;
    QPushButton *btnOpenReadyIpaDir;
    QWidget *tabBackupSender;
    QGroupBox *groupBox_4;
    QComboBox *comboBoxTasks;
    QPushButton *btnSendBackups;
    QGroupBox *groupBox_5;
    QTextBrowser *textBrowserSendLog;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(729, 777);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        actionOpenTasksDir = new QAction(MainWindow);
        actionOpenTasksDir->setObjectName(QStringLiteral("actionOpenTasksDir"));
        actionOpenCurrentTaskDir = new QAction(MainWindow);
        actionOpenCurrentTaskDir->setObjectName(QStringLiteral("actionOpenCurrentTaskDir"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 170, 121, 16));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 701, 581));
        tabInstaller = new QWidget();
        tabInstaller->setObjectName(QStringLiteral("tabInstaller"));
        groupBox = new QGroupBox(tabInstaller);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 10, 691, 80));
        whatsappAppcheckBox = new QCheckBox(groupBox);
        whatsappAppcheckBox->setObjectName(QStringLiteral("whatsappAppcheckBox"));
        whatsappAppcheckBox->setGeometry(QRect(20, 20, 91, 17));
        whatsappAppcheckBox->setChecked(true);
        TelegramAppCheckBox = new QCheckBox(groupBox);
        TelegramAppCheckBox->setObjectName(QStringLiteral("TelegramAppCheckBox"));
        TelegramAppCheckBox->setGeometry(QRect(20, 40, 91, 17));
        TelegramAppCheckBox->setChecked(true);
        WechatAppCheckBox = new QCheckBox(groupBox);
        WechatAppCheckBox->setObjectName(QStringLiteral("WechatAppCheckBox"));
        WechatAppCheckBox->setGeometry(QRect(140, 20, 70, 17));
        WechatAppCheckBox->setChecked(true);
        ViberAppCheckBox = new QCheckBox(groupBox);
        ViberAppCheckBox->setObjectName(QStringLiteral("ViberAppCheckBox"));
        ViberAppCheckBox->setGeometry(QRect(140, 40, 70, 17));
        ViberAppCheckBox->setChecked(true);
        groupBox_2 = new QGroupBox(tabInstaller);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 100, 691, 71));
        guidLine = new QLineEdit(groupBox_2);
        guidLine->setObjectName(QStringLiteral("guidLine"));
        guidLine->setGeometry(QRect(10, 20, 441, 20));
        guidLine->setReadOnly(true);
        chooseFileBtn = new QPushButton(groupBox_2);
        chooseFileBtn->setObjectName(QStringLiteral("chooseFileBtn"));
        chooseFileBtn->setGeometry(QRect(470, 20, 121, 23));
        groupBox_3 = new QGroupBox(tabInstaller);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 170, 691, 81));
        backupsListComBox = new QComboBox(groupBox_3);
        backupsListComBox->setObjectName(QStringLiteral("backupsListComBox"));
        backupsListComBox->setGeometry(QRect(10, 20, 651, 22));
        backupsListComBox->setEditable(true);
        noRestoreCheckBox = new QCheckBox(groupBox_3);
        noRestoreCheckBox->setObjectName(QStringLiteral("noRestoreCheckBox"));
        noRestoreCheckBox->setGeometry(QRect(20, 50, 251, 21));
        startBtn = new QPushButton(tabInstaller);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setGeometry(QRect(290, 260, 75, 23));
        label_2 = new QLabel(tabInstaller);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(290, 300, 81, 20));
        logTextBrowser = new QTextBrowser(tabInstaller);
        logTextBrowser->setObjectName(QStringLiteral("logTextBrowser"));
        logTextBrowser->setGeometry(QRect(0, 330, 691, 171));
        btnOpenReadyIpaDir = new QPushButton(tabInstaller);
        btnOpenReadyIpaDir->setObjectName(QStringLiteral("btnOpenReadyIpaDir"));
        btnOpenReadyIpaDir->setGeometry(QRect(280, 510, 131, 32));
        tabWidget->addTab(tabInstaller, QString());
        tabBackupSender = new QWidget();
        tabBackupSender->setObjectName(QStringLiteral("tabBackupSender"));
        groupBox_4 = new QGroupBox(tabBackupSender);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 30, 651, 121));
        comboBoxTasks = new QComboBox(groupBox_4);
        comboBoxTasks->setObjectName(QStringLiteral("comboBoxTasks"));
        comboBoxTasks->setGeometry(QRect(10, 40, 531, 26));
        btnSendBackups = new QPushButton(groupBox_4);
        btnSendBackups->setObjectName(QStringLiteral("btnSendBackups"));
        btnSendBackups->setGeometry(QRect(540, 40, 113, 32));
        groupBox_5 = new QGroupBox(tabBackupSender);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 170, 651, 221));
        textBrowserSendLog = new QTextBrowser(groupBox_5);
        textBrowserSendLog->setObjectName(QStringLiteral("textBrowserSendLog"));
        textBrowserSendLog->setGeometry(QRect(10, 31, 631, 181));
        tabWidget->addTab(tabBackupSender, QString());
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 729, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action);
        menu_2->addAction(actionOpenTasksDir);
        menu_2->addAction(actionOpenCurrentTaskDir);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "itunesBackupParser", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\210\320\260\320\263\320\276\320\262\320\260\321\217 \320\230\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217", Q_NULLPTR));
        actionOpenTasksDir->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\216 \321\201 \320\267\320\260\320\264\320\260\320\275\320\270\321\217\320\274\320\270", Q_NULLPTR));
        actionOpenCurrentTaskDir->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\216 \321\201 \321\202\320\265\320\272\321\203\321\211\320\270\320\274 \320\267\320\260\320\264\320\260\320\275\320\270\320\265\320\274", Q_NULLPTR));
        label_3->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217 \320\272\320\276\321\202\320\276\321\200\321\213\320\265 \320\261\321\203\320\264\321\203\321\202 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\321\213 \320\275\320\260 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", Q_NULLPTR));
        whatsappAppcheckBox->setText(QApplication::translate("MainWindow", "Whatsapp ", Q_NULLPTR));
        TelegramAppCheckBox->setText(QApplication::translate("MainWindow", "Telegram", Q_NULLPTR));
        WechatAppCheckBox->setText(QApplication::translate("MainWindow", "Wechat", Q_NULLPTR));
        ViberAppCheckBox->setText(QApplication::translate("MainWindow", "Viber", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \321\201 guid", Q_NULLPTR));
        guidLine->setPlaceholderText(QApplication::translate("MainWindow", "empty", Q_NULLPTR));
        chooseFileBtn->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\261\321\215\320\272\320\260\320\277 \320\270\320\273\320\270 \320\262\320\262\320\265\320\264\320\270\321\202\320\265 UDID \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260 \321\201 iTunes", Q_NULLPTR));
        noRestoreCheckBox->setText(QApplication::translate("MainWindow", "\320\235\320\265 \320\262\320\276\321\201\321\201\321\202\320\260\320\275\320\260\320\262\320\273\320\270\320\262\320\260\321\202\321\214 \320\262\320\270\320\264\320\265\320\276 \321\204\320\260\320\271\320\273\321\213", Q_NULLPTR));
        startBtn->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", Q_NULLPTR));
        btnOpenReadyIpaDir->setText(QApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\321\213\320\265 \320\277\320\260\320\272\320\265\321\202\321\213", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabInstaller), QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\321\211\320\270\320\272", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", Q_NULLPTR));
        btnSendBackups->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabBackupSender), QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\272\320\260 \320\260\321\200\321\205\320\270\320\262\320\276\320\262", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\320\230\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\276\321\207\320\275\321\213\320\265 \320\277\320\260\320\272\320\265\321\202\321\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
