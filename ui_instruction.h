/********************************************************************************
** Form generated from reading UI file 'instruction.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTRUCTION_H
#define UI_INSTRUCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Instruction
{
public:
    QTextBrowser *textBrowser;
    QLabel *label;
    QLineEdit *installUrllineEdit;

    void setupUi(QWidget *Instruction)
    {
        if (Instruction->objectName().isEmpty())
            Instruction->setObjectName(QStringLiteral("Instruction"));
        Instruction->resize(860, 541);
        textBrowser = new QTextBrowser(Instruction);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 50, 831, 481));
        label = new QLabel(Instruction);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 141, 16));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        installUrllineEdit = new QLineEdit(Instruction);
        installUrllineEdit->setObjectName(QStringLiteral("installUrllineEdit"));
        installUrllineEdit->setGeometry(QRect(210, 10, 531, 31));
        QPalette palette;
        QBrush brush(QColor(0, 170, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        installUrllineEdit->setPalette(palette);
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        installUrllineEdit->setFont(font1);
        installUrllineEdit->setReadOnly(true);

        retranslateUi(Instruction);

        QMetaObject::connectSlotsByName(Instruction);
    } // setupUi

    void retranslateUi(QWidget *Instruction)
    {
        Instruction->setWindowTitle(QApplication::translate("Instruction", "\320\237\320\276\321\210\320\260\320\263\320\260\320\262\320\260\321\217 \320\270\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217.", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("Instruction", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#aa0000;\">\320\237\320\276\321\210\320\260\320\263\320\260\320\262\320\260\321\217 \320\270\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\321\217. </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-inden"
                        "t:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#aa0000;\">\320\222\321\213\320\277\320\276\320\273\320\275\321\217\320\271\321\202\320\265 \320\262\321\201\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217 \320\262 \321\202\320\276\320\274 \320\277\320\276\321\200\321\217\320\264\320\272\320\265 \320\262 \320\272\320\276\321\202\320\276\321\200\320\276\320\274 \320\276\320\275\320\270 \320\275\320\260\320\277\320\270\321\201\320\260\320\275\321\213!</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt; text-decoration: underline;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -q"
                        "t-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">1.\320\236\321\202\320\272\321\200\320\276\320\271\321\202\320\265 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\320\265 Whatsapp \320\275\320\260 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\265 \320\270 \320\267\320\260\320\271\320\264\320\270\321\202\320\265 \320\262 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 </span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14"
                        "pt;\">2. \320\227\320\260\320\277\320\276\320\274\320\275\320\270\321\202\320\265 \320\270\320\273\320\270 \320\267\320\260\320\277\320\270\321\210\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\262\320\273\320\260\320\264\320\265\320\273\321\214\321\206\320\260 Whatsapp, \321\200\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\275\320\276\320\265 \321\200\321\217\320\264\320\276\320\274 \321\201 \320\260\320\262\320\260\321\202\320\260\321\200\320\276\320\274</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0269.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-le"
                        "ft:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">3. \320\243\320\264\320\260\320\273\320\270\321\202\320\265 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\320\265 Whatsapp c \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260 (\320\264\320\276\320\273\320\263\320\276\320\265 \320\275\320\260\320\266\320\260\321\202\320\270\320\265 \320\275\320\260 \320\270\320\272\320\276\320\275\320\272\321\203 Whatsapp, \320\264\320\260\320\273\320\265\320\265 \320\275\320\260\320\266\320\260\321\202\321\214 \320\275\320\260 \320\277\320\276\321\217\320\262\320\270\320\262\320\270\321\210\320\270\320\271\321\201\321\217 \320\272\321\200\320\265\321\201\321\202\320\270\320\272 \321\203 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217, \320\277\320\276\321\201\320\273\320\265 \321\203\320\264\320\260\320\273\320\265\320\275\320\270\321\217 \320\270\320\272\320\276\320\275\320\272\321\203\320\270"
                        " \320\275\320\260\320\266\320\260\321\202\321\214 \320\272\320\275\320\276\320\270\320\272\321\203 &quot;Home&quot; )</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0278.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">4. \320\236\321\202\320\272\321\200\320\276\320\271\321\202\320\265 \320\261\321\200\320\260\321\203\320\267\320\265\321\200 Safari \320\270 \320\262"
                        "\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\203\321\216 \321\201\321\201\321\213\320\273\320\272\321\203 \320\264\320\273\321\217 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\270 (\321\201\320\274 \320\262\320\262\320\265\321\200\321\205\321\203 \320\276\320\272\320\275\320\260 \320\264\320\260\320\275\320\275\320\276\320\271 \320\270\320\275\321\201\321\202\321\200\321\203\320\272\321\206\320\270\320\270). \320\236\321\202\320\272\321\200\320\276\320\265\321\202\321\201\321\217 \321\201\321\202\321\200\320\260\320\275\320\270\321\206\320\260 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\270 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217 Whatsapp. \320\225\321\201\320\273\320\270 \321\201\321\202\321\200\320\260\320\275\320\270\321\206\320\260 \320\275\320\265 \320\276\321\202\320\272\321\200\321\213\320\273\320\260\321\201\321\214 \320\275\321\203\320\266\320"
                        "\275\320\276 \320\277\320\276\320\264\320\276\320\266\320\264\320\260\321\202\321\214 \320\270 \320\276\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\321\200\320\276\321\201 \320\277\320\276 \321\201\321\201\321\213\320\273\320\272\320\270 \320\262 \320\261\321\200\320\260\321\203\320\267\320\265\321\200\320\265.</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">5. \320\232\320\276\320\263\320\264\320\260 \320\275\320\260 \321\201\321\202\321\200\320\260\320\275\320\270\321\206\320\265 \320\277\320\276\321\217\320\262\320\270\321\202\321\201\321\217 \320\275\320\260\320\264\320\277\320\270\321\201\321\214 \320\267\320\265\320\273\320\265\320\275\320\276\320\263\320\276"
                        " \321\206\320\262\320\265\321\202\320\260 \320\275\320\260\320\266\320\274\320\270\321\202\320\265 \320\275\320\260 \321\215\321\202\321\203 \320\275\320\260\320\264\320\277\320\270\321\201\321\214.</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0270.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">6. \320\237\321\200\320\270 \320\277\320\276\321\217"
                        "\320\262\320\273\320\265\320\275\320\270\320\270 \320\262\321\201\320\277\320\273\321\213\320\262\320\260\321\216\321\211\320\265\320\263\320\276 \320\276\320\272\320\275\320\260 \320\275\320\260\320\266\320\274\320\270\321\202\320\265 &quot;Install&quot;(&quot;\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214&quot;)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0271.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margi"
                        "n-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">7. \320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\272\320\275\320\276\320\277\320\272\321\203 &quot;Home&quot; \320\270 \320\277\320\265\321\200\320\265\320\271\320\264\320\270\321\202\320\265 \320\275\320\260 \320\263\320\273\320\260\320\262\320\275\321\213\320\271 \321\215\320\272\321\200\320\260\320\275.</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">8. \320\235\320\260 \321\215\320\272\321\200\320\260\320\275\320\265 \320\277\320\276\321\217\320\262\320\270\321\202\321\201\321\217 \320\270\320\272\320\276\320\275\320\272\320\260 \321\201 \320\275\320\260\320\264\320\277\320\270\321"
                        "\201\321\214\321\216 &quot;Waiting&quot;/&quot;\320\236\320\266\320\270\320\264\320\260\320\271\321\202\320\265&quot; (\321\201\320\274 \320\275\320\260 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\320\265), \320\264\320\276\320\266\320\264\320\270\321\202\320\265\321\201\321\214 \320\277\320\276\320\272\320\260 \320\270\320\272\320\276\320\275\320\272\320\260 \320\275\320\265 \320\270\320\267\320\274\320\265\320\275\320\270\321\202\321\201\321\217 \320\275\320\260 \320\270\320\272\320\276\320\275\320\272\321\203 Whatsapp</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0272.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; ma"
                        "rgin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">9. \320\237\320\276\321\201\320\273\320\265 \321\202\320\276\320\263\320\276 \320\272\320\260\320\272 \320\270\320\272\320\276\320\275\320\272\320\260 \320\270\320\267\320\274\320\265\320\275\320\270\320\273\320\260\321\201\321\214 \320\275\320\260 \320\270\320\272\320\276\320\275\320\272\321\203 Whatsapp  \320\275\320\260\320\266\320\274\320\270\321\202\320\265 \320\275\320\260 \320\270\320\272\320\276\320\275\320\272\321\203</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-i"
                        "ndent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">10.\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\320\265 \320\267\320\260\320\277\321\200\320\260\321\210\320\270\320\262\320\260\320\265\320\274\321\213\320\265 \320\264\320\276\321\201\321\202\321\203\320\277\321\213 \320\272 \320\272\320\276\320\275\321\202\320\260\320\272\321\202\320\260\320\274, \320\263\320\265\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\216 \320\270 \321\203\320\262\320\265\320\264\320\276\320\274\320\273\320\265\320\275\320\270\321\217\320\274 (\320\235\320\260\320\266\320\260\321\202\321\214 &quot;Allow&quot;/&quot;\320\240\320\260\320\267\321\200\320\265\321\210\320\270\321\202\321\214&quot;)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0p"
                        "x; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0274.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">11. \320\222\320\262\320\265\321\201\321\202\320\270 \320\275\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\275\321\213\320\271 \320\262 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\265 </span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text"
                        "-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0275.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">12. \320\225\321\201\320\273\320\270 \320\261\321\203\320\264\320\265\321\202 \320\267\320\260\320\277\321\200\320\276\321\210\320\265\320\275 \320\272\320\276\320\264, \320\264\320\276\320\266\320\264\320\270\321\202\320\265\321\201\321\214 \320\277\321\200\320\270\321\205\320\276\320\264\320\260 SMS \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217, \320\270 \320\262\320\262\320\265\320"
                        "\264\320\270\321\202\320\265 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \320\272\320\276\320\264 \320\262 \320\267\320\260\320\277\321\200\320\260\321\210\320\270\320\262\320\260\320\265\320\274\320\276\320\265 \320\277\320\276\320\273\320\265</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">13. \320\224\320\260\320\273\320\265\320\265 \320\262 \320\277\320\276\320\273\320\265 &quot;Profile&quot;/&quot;\320\237\321\200\320\276\321\204\320\270\320\273\321\214&quot; \320\270\320\274\321\217 \320\262\320\273\320\260\320\264\320\265\320\273\321\214\321\206\320\260 \320\272\320\260\320\272 \320\276\320\275\320\276 \320\261\321\213\320\273\320\276 \321\203\320\272\320\260\320\267\320\260"
                        "\320\275\320\276 \320\262 \320\276\321\200\320\270\320\263\320\270\320\275\320\260\320\273\321\214\320\275\320\276\320\274 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\320\270 (\321\201\320\274 \320\277\321\203\320\275\320\272\321\202 2)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">14. \320\236\321\202\320\272\321\200\320\276\320\265\321\202\321\201\321\217 \321\201\321\202\321\200\320\260\320\275\320\270\321\206\320\260 \321\201 \320\262\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\275\321\213\320\274\320\270 \321\207\320\260\321\202\320\260\320\274\320\270</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0p"
                        "x; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">15. \320\236\321\202\320\272\321\200\320\276\320\271\321\202\320\265 \320\261\321\200\320\260\321\203\320\267\320\265\321\200 Safari \320\270 \320\275\320\260\320\266\320\274\320\270\321\202\320\265 \320\275\320\260 \320\267\320\275\320\260\321\207\320\265\320\272 \320\272\320\275\320\270\320\266\320\272\320\270 \320\262\320\275\320\270\320\267\321\203 \320\276\320\272\320\275\320\260, \320\264\320\260\320\273\320\265\320\265 \321\201\321\201\321\213\320\273\320\272\320\260 &quot;History&quot;/&quot;\320\230\321\201\321\202\320\276\321\200\320\270\321\217&quot;</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><"
                        "br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0276.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">16. \320\243\320\264\320\260\320\273\320\270\321\202\320\265 \321\201\321\201\321\213\320\273\320\272\321\203 \320\262\320\262\320\265\320\264\320\265\320\275\321\203\321\216 \320\262\320\260\320\274\320\270 \321\200\320\260\320\275\320\265\320\265 \320\264\320\273\321\217 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\270 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217 (\321\201\320\273"
                        "\320\260\320\271\320\264 \321\201\320\277\321\200\320\260\320\262\320\260 \320\275\320\260\320\273\320\265\320\262\320\276, \320\275\320\260\320\266\320\260\321\202\321\214 Delete)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/screen/IMG_0277.PNG\" width=\"400\" height=\"600\" /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">17. \320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\272"
                        "\320\275\320\276\320\277\320\272\321\203 &quot;Home&quot;/&quot;\320\224\320\276\320\274\320\276\320\271&quot;, \320\262\321\213\320\272\320\273\321\216\321\207\320\270\321\202\320\265 \321\215\320\272\321\200\320\260\320\275</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">18. \320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\267\320\260\320\262\320\265\321\200\321\210\320\265\320\275\320\260</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:"
                        "0px; -qt-block-indent:0; text-indent:0px;\"> </p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("Instruction", "\320\241\321\201\321\213\320\273\320\272\320\260 \320\264\320\273\321\217 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\270:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Instruction: public Ui_Instruction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTRUCTION_H
