/********************************************************************************
** Form generated from reading UI file 'wechat_install_guide.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WECHAT_INSTALL_GUIDE_H
#define UI_WECHAT_INSTALL_GUIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormWechatGuide
{
public:

    void setupUi(QWidget *FormWechatGuide)
    {
        if (FormWechatGuide->objectName().isEmpty())
            FormWechatGuide->setObjectName(QStringLiteral("FormWechatGuide"));
        FormWechatGuide->resize(400, 300);

        retranslateUi(FormWechatGuide);

        QMetaObject::connectSlotsByName(FormWechatGuide);
    } // setupUi

    void retranslateUi(QWidget *FormWechatGuide)
    {
        FormWechatGuide->setWindowTitle(QApplication::translate("FormWechatGuide", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class FormWechatGuide: public Ui_FormWechatGuide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WECHAT_INSTALL_GUIDE_H
