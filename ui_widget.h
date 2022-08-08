/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *selDllBtn;
    QTextEdit *showSelDll;
    QTableWidget *procTable;
    QPushButton *updateProcBtn;
    QPushButton *submitBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(600, 410);
        selDllBtn = new QPushButton(Widget);
        selDllBtn->setObjectName(QString::fromUtf8("selDllBtn"));
        selDllBtn->setGeometry(QRect(30, 20, 101, 41));
        showSelDll = new QTextEdit(Widget);
        showSelDll->setObjectName(QString::fromUtf8("showSelDll"));
        showSelDll->setEnabled(false);
        showSelDll->setGeometry(QRect(160, 10, 401, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \347\271\201\351\273\221\351\253\224 Std B"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        showSelDll->setFont(font);
        procTable = new QTableWidget(Widget);
        procTable->setObjectName(QString::fromUtf8("procTable"));
        procTable->setGeometry(QRect(30, 90, 531, 251));
        updateProcBtn = new QPushButton(Widget);
        updateProcBtn->setObjectName(QString::fromUtf8("updateProcBtn"));
        updateProcBtn->setGeometry(QRect(30, 350, 141, 41));
        submitBtn = new QPushButton(Widget);
        submitBtn->setObjectName(QString::fromUtf8("submitBtn"));
        submitBtn->setGeometry(QRect(420, 350, 141, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        selDllBtn->setText(QCoreApplication::translate("Widget", "\351\201\270\346\223\207Dll", nullptr));
        showSelDll->setMarkdown(QString());
        showSelDll->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Adobe \347\271\201\351\273\221\351\253\224 Std B'; font-size:10pt; font-weight:600; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p></body></html>", nullptr));
        updateProcBtn->setText(QCoreApplication::translate("Widget", "\345\210\267\346\226\260\351\200\262\347\250\213\345\210\227\350\241\250", nullptr));
        submitBtn->setText(QCoreApplication::translate("Widget", "\347\242\272\345\256\232\346\263\250\345\205\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
