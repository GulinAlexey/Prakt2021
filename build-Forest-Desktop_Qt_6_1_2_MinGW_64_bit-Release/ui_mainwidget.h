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
#include <QtWidgets/QFrame>
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
    QGroupBox *vzaimode;
    QRadioButton *plant_b;
    QRadioButton *delete_b;
    QRadioButton *infoplant_b;
    QRadioButton *infodirt_b;
    QGroupBox *timemode;
    QRadioButton *normal_b;
    QRadioButton *speed_b;
    QRadioButton *pause_b;
    QLabel *pogoda;
    QFrame *place;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *type_plant;
    QRadioButton *grass_type;
    QRadioButton *bush_type;
    QRadioButton *tree_type;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(1159, 660);
        MainWidget->setMinimumSize(QSize(1159, 660));
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWidget->setWindowIcon(icon);
        statusbar = new QStatusBar(MainWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 18));
        vzaimode = new QGroupBox(MainWidget);
        vzaimode->setObjectName(QString::fromUtf8("vzaimode"));
        vzaimode->setGeometry(QRect(940, 20, 181, 131));
        vzaimode->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 227, 187);"));
        plant_b = new QRadioButton(vzaimode);
        plant_b->setObjectName(QString::fromUtf8("plant_b"));
        plant_b->setGeometry(QRect(10, 20, 111, 17));
        plant_b->setChecked(true);
        delete_b = new QRadioButton(vzaimode);
        delete_b->setObjectName(QString::fromUtf8("delete_b"));
        delete_b->setGeometry(QRect(10, 40, 121, 17));
        infoplant_b = new QRadioButton(vzaimode);
        infoplant_b->setObjectName(QString::fromUtf8("infoplant_b"));
        infoplant_b->setGeometry(QRect(10, 60, 121, 17));
        infodirt_b = new QRadioButton(vzaimode);
        infodirt_b->setObjectName(QString::fromUtf8("infodirt_b"));
        infodirt_b->setGeometry(QRect(10, 80, 101, 17));
        timemode = new QGroupBox(MainWidget);
        timemode->setObjectName(QString::fromUtf8("timemode"));
        timemode->setGeometry(QRect(940, 280, 181, 101));
        timemode->setStyleSheet(QString::fromUtf8("background-color: rgb(205, 208, 255);"));
        normal_b = new QRadioButton(timemode);
        normal_b->setObjectName(QString::fromUtf8("normal_b"));
        normal_b->setGeometry(QRect(10, 20, 91, 17));
        normal_b->setChecked(true);
        speed_b = new QRadioButton(timemode);
        speed_b->setObjectName(QString::fromUtf8("speed_b"));
        speed_b->setGeometry(QRect(10, 40, 91, 17));
        pause_b = new QRadioButton(timemode);
        pause_b->setObjectName(QString::fromUtf8("pause_b"));
        pause_b->setGeometry(QRect(10, 60, 82, 17));
        pogoda = new QLabel(MainWidget);
        pogoda->setObjectName(QString::fromUtf8("pogoda"));
        pogoda->setGeometry(QRect(830, 20, 90, 90));
        pogoda->setScaledContents(true);
        place = new QFrame(MainWidget);
        place->setObjectName(QString::fromUtf8("place"));
        place->setEnabled(true);
        place->setGeometry(QRect(20, 20, 800, 600));
        place->setStyleSheet(QString::fromUtf8("background-color: rgb(47, 28, 11)"));
        place->setFrameShape(QFrame::StyledPanel);
        place->setFrameShadow(QFrame::Raised);
        label = new QLabel(place);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 47, 13));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(47, 28, 11, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label->setPalette(palette);
        label_2 = new QLabel(place);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 60, 47, 13));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_2->setPalette(palette1);
        type_plant = new QGroupBox(MainWidget);
        type_plant->setObjectName(QString::fromUtf8("type_plant"));
        type_plant->setGeometry(QRect(940, 163, 181, 101));
        type_plant->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 255, 188);"));
        grass_type = new QRadioButton(type_plant);
        grass_type->setObjectName(QString::fromUtf8("grass_type"));
        grass_type->setGeometry(QRect(10, 20, 111, 17));
        grass_type->setChecked(true);
        bush_type = new QRadioButton(type_plant);
        bush_type->setObjectName(QString::fromUtf8("bush_type"));
        bush_type->setGeometry(QRect(10, 40, 121, 17));
        tree_type = new QRadioButton(type_plant);
        tree_type->setObjectName(QString::fromUtf8("tree_type"));
        tree_type->setGeometry(QRect(10, 60, 121, 17));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "\320\240\320\260\321\201\321\202\320\270\321\202\320\265\320\273\321\214\320\275\320\276\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\321\201\321\202\320\262\320\276", nullptr));
        vzaimode->setTitle(QCoreApplication::translate("MainWidget", "\320\240\320\265\320\266\320\270\320\274 \320\262\320\267\320\260\320\270\320\274\320\276\320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
        plant_b->setText(QCoreApplication::translate("MainWidget", "\320\241\320\260\320\264\320\270\321\202\321\214 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\320\265", nullptr));
        delete_b->setText(QCoreApplication::translate("MainWidget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\320\265", nullptr));
        infoplant_b->setText(QCoreApplication::translate("MainWidget", "\320\230\320\275\321\204\320\276 \320\276 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\320\270", nullptr));
        infodirt_b->setText(QCoreApplication::translate("MainWidget", "\320\230\320\275\321\204\320\276 \320\276 \320\277\320\276\321\207\320\262\320\265", nullptr));
        timemode->setTitle(QCoreApplication::translate("MainWidget", "\320\240\320\265\320\266\320\270\320\274 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        normal_b->setText(QCoreApplication::translate("MainWidget", "\320\235\320\276\321\200\320\274\320\260\320\273\321\214\320\275\321\213\320\271", nullptr));
        speed_b->setText(QCoreApplication::translate("MainWidget", "\320\243\321\201\320\272\320\276\321\200\320\265\320\275\320\275\321\213\320\271", nullptr));
        pause_b->setText(QCoreApplication::translate("MainWidget", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        pogoda->setText(QString());
        label->setText(QCoreApplication::translate("MainWidget", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("MainWidget", "TextLabel", nullptr));
        type_plant->setTitle(QCoreApplication::translate("MainWidget", "\320\222\320\270\320\264 \321\200\320\260\321\201\321\202\320\265\320\275\320\270\321\217 \320\264\320\273\321\217 \320\277\320\276\321\201\320\260\320\264\320\272\320\270", nullptr));
        grass_type->setText(QCoreApplication::translate("MainWidget", "\320\235\320\276\320\262\320\260\321\217 \321\202\321\200\320\260\320\262\320\260", nullptr));
        bush_type->setText(QCoreApplication::translate("MainWidget", "\320\235\320\276\320\262\321\213\320\271 \320\272\321\203\321\201\321\202", nullptr));
        tree_type->setText(QCoreApplication::translate("MainWidget", "\320\235\320\276\320\262\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
