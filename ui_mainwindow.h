/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralWidget;
    QPushButton *startBtn;
    QTextBrowser *logTextBrowser;
    QLabel *label_2;
    QLabel *label_3;
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
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(729, 556);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        startBtn = new QPushButton(centralWidget);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setGeometry(QRect(290, 260, 75, 23));
        logTextBrowser = new QTextBrowser(centralWidget);
        logTextBrowser->setObjectName(QStringLiteral("logTextBrowser"));
        logTextBrowser->setGeometry(QRect(10, 320, 691, 171));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 290, 61, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 170, 121, 16));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 691, 80));
        whatsappAppcheckBox = new QCheckBox(groupBox);
        whatsappAppcheckBox->setObjectName(QStringLiteral("whatsappAppcheckBox"));
        whatsappAppcheckBox->setGeometry(QRect(20, 20, 70, 17));
        whatsappAppcheckBox->setChecked(true);
        TelegramAppCheckBox = new QCheckBox(groupBox);
        TelegramAppCheckBox->setObjectName(QStringLiteral("TelegramAppCheckBox"));
        TelegramAppCheckBox->setGeometry(QRect(20, 40, 70, 17));
        TelegramAppCheckBox->setChecked(true);
        WechatAppCheckBox = new QCheckBox(groupBox);
        WechatAppCheckBox->setObjectName(QStringLiteral("WechatAppCheckBox"));
        WechatAppCheckBox->setGeometry(QRect(110, 20, 70, 17));
        WechatAppCheckBox->setChecked(true);
        ViberAppCheckBox = new QCheckBox(groupBox);
        ViberAppCheckBox->setObjectName(QStringLiteral("ViberAppCheckBox"));
        ViberAppCheckBox->setEnabled(false);
        ViberAppCheckBox->setGeometry(QRect(110, 40, 70, 17));
        ViberAppCheckBox->setChecked(false);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 100, 691, 61));
        guidLine = new QLineEdit(groupBox_2);
        guidLine->setObjectName(QStringLiteral("guidLine"));
        guidLine->setGeometry(QRect(10, 20, 441, 20));
        guidLine->setReadOnly(true);
        chooseFileBtn = new QPushButton(groupBox_2);
        chooseFileBtn->setObjectName(QStringLiteral("chooseFileBtn"));
        chooseFileBtn->setGeometry(QRect(470, 20, 91, 23));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 170, 691, 81));
        backupsListComBox = new QComboBox(groupBox_3);
        backupsListComBox->setObjectName(QStringLiteral("backupsListComBox"));
        backupsListComBox->setGeometry(QRect(10, 20, 651, 22));
        backupsListComBox->setEditable(true);
        noRestoreCheckBox = new QCheckBox(groupBox_3);
        noRestoreCheckBox->setObjectName(QStringLiteral("noRestoreCheckBox"));
        noRestoreCheckBox->setGeometry(QRect(20, 50, 211, 21));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 729, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "itunesBackupParser", 0));
        action->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\210\320\260\320\263\320\276\320\262\320\260\321\217 \320\230\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217", 0));
        startBtn->setText(QApplication::translate("MainWindow", "Start", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", 0));
        label_3->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217 \320\272\320\276\321\202\320\276\321\200\321\213\320\265 \320\261\321\203\320\264\321\203\321\202 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\321\213 \320\275\320\260 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", 0));
        whatsappAppcheckBox->setText(QApplication::translate("MainWindow", "Whatsapp ", 0));
        TelegramAppCheckBox->setText(QApplication::translate("MainWindow", "Telegram", 0));
        WechatAppCheckBox->setText(QApplication::translate("MainWindow", "Wechat", 0));
        ViberAppCheckBox->setText(QApplication::translate("MainWindow", "Viber", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \321\201 guid", 0));
        guidLine->setPlaceholderText(QApplication::translate("MainWindow", "empty", 0));
        chooseFileBtn->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\261\321\215\320\272\320\260\320\277 \320\270\320\273\320\270 \320\262\320\262\320\265\320\264\320\270\321\202\320\265 UDID \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260 \321\201 iTunes", 0));
        noRestoreCheckBox->setText(QApplication::translate("MainWindow", "\320\235\320\265 \320\262\320\276\321\201\321\201\321\202\320\260\320\275\320\260\320\262\320\273\320\270\320\262\320\260\321\202\321\214 \320\262\320\270\320\264\320\265\320\276 \321\204\320\260\320\271\320\273\321\213", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\230\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
