/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QStatusBar *statusbar;
    QGroupBox *place;
    QGroupBox *vzaimode;
    QRadioButton *sad_b;
    QRadioButton *ud_b;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *timemode;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QLabel *pogoda;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(1159, 660);
        MainWidget->setMinimumSize(QSize(1074, 660));
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWidget->setWindowIcon(icon);
        statusbar = new QStatusBar(MainWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 18));
        place = new QGroupBox(MainWidget);
        place->setObjectName(QString::fromUtf8("place"));
        place->setGeometry(QRect(20, 20, 800, 600));
        place->setMouseTracking(true);
        place->setAutoFillBackground(false);
        place->setStyleSheet(QString::fromUtf8("background-color: rgb(47, 28, 11)"));
        vzaimode = new QGroupBox(MainWidget);
        vzaimode->setObjectName(QString::fromUtf8("vzaimode"));
        vzaimode->setGeometry(QRect(940, 20, 181, 131));
        sad_b = new QRadioButton(vzaimode);
        sad_b->setObjectName(QString::fromUtf8("sad_b"));
        sad_b->setGeometry(QRect(10, 20, 111, 17));
        ud_b = new QRadioButton(vzaimode);
        ud_b->setObjectName(QString::fromUtf8("ud_b"));
        ud_b->setGeometry(QRect(10, 40, 121, 17));
        radioButton_3 = new QRadioButton(vzaimode);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 60, 121, 17));
        radioButton_4 = new QRadioButton(vzaimode);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 80, 101, 17));
        timemode = new QGroupBox(MainWidget);
        timemode->setObjectName(QString::fromUtf8("timemode"));
        timemode->setGeometry(QRect(940, 170, 181, 101));
        radioButton_5 = new QRadioButton(timemode);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 20, 91, 17));
        radioButton_6 = new QRadioButton(timemode);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(10, 40, 91, 17));
        radioButton_7 = new QRadioButton(timemode);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        radioButton_7->setGeometry(QRect(10, 60, 82, 17));
        pogoda = new QLabel(MainWidget);
        pogoda->setObjectName(QString::fromUtf8("pogoda"));
        pogoda->setGeometry(QRect(830, 20, 47, 13));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "\320\240\320\260\321\201\321\202\320\270\321\202\320\265\320\273\321\214\320\275\320\276\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\321\201\321\202\320\262\320\276", nullptr));
        place->setTitle(QString());
        vzaimode->setTitle(QCoreApplication::translate("MainWidget", "\320\240\320\265\320\266\320\270\320\274 \320\262\320\267\320\260\320\270\320\274\320\276\320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
        sad_b->setText(QCoreApplication::translate("MainWidget", "\320\241\320\260\320\264\320\270\321\202\321\214 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\320\265", nullptr));
        ud_b->setText(QCoreApplication::translate("MainWidget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\320\265", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWidget", "\320\230\320\275\321\204\320\276 \320\276 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\320\270", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWidget", "\320\230\320\275\321\204\320\276 \320\276 \320\277\320\276\321\207\320\262\320\265", nullptr));
        timemode->setTitle(QCoreApplication::translate("MainWidget", "\320\240\320\265\320\266\320\270\320\274 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWidget", "\320\235\320\276\321\200\320\274\320\260\320\273\321\214\320\275\321\213\320\271", nullptr));
        radioButton_6->setText(QCoreApplication::translate("MainWidget", "\320\243\321\201\320\272\320\276\321\200\320\265\320\275\320\275\321\213\320\271", nullptr));
        radioButton_7->setText(QCoreApplication::translate("MainWidget", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        pogoda->setText(QCoreApplication::translate("MainWidget", "p", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
