/********************************************************************************
** Form generated from reading UI file 'console.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Console
{
public:
    QGroupBox *groupBox_0;
    QLabel *label_time;
    QGroupBox *groupBox_1;
    QPushButton *pushButton_last;
    QPushButton *pushButton_play;
    QPushButton *pushButton_next;
    QSlider *slider_voice;
    QPushButton *pushButton_love;
    QPushButton *pushButton_voice;
    QPushButton *pushButton_order;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_speed;
    QPushButton *pushButton_upend;
    QPushButton *pushButton_set;
    QPushButton *pushButton_screen;
    QSlider *slider_frame;

    void setupUi(QWidget *Console)
    {
        if (Console->objectName().isEmpty())
            Console->setObjectName(QString::fromUtf8("Console"));
        Console->resize(1000, 80);
        QFont font;
        font.setStrikeOut(false);
        Console->setFont(font);
        Console->setAutoFillBackground(false);
        Console->setStyleSheet(QString::fromUtf8(""));
        groupBox_0 = new QGroupBox(Console);
        groupBox_0->setObjectName(QString::fromUtf8("groupBox_0"));
        groupBox_0->setEnabled(true);
        groupBox_0->setGeometry(QRect(0, 20, 161, 41));
        groupBox_0->setFont(font);
        groupBox_0->setAutoFillBackground(false);
        groupBox_0->setStyleSheet(QString::fromUtf8("border:none"));
        label_time = new QLabel(groupBox_0);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(10, 10, 141, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font1.setPointSize(10);
        font1.setStrikeOut(false);
        label_time->setFont(font1);
        groupBox_1 = new QGroupBox(Console);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        groupBox_1->setGeometry(QRect(230, 20, 501, 41));
        groupBox_1->setStyleSheet(QString::fromUtf8("border:none"));
        pushButton_last = new QPushButton(groupBox_1);
        pushButton_last->setObjectName(QString::fromUtf8("pushButton_last"));
        pushButton_last->setGeometry(QRect(70, 0, 41, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/last.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_last->setIcon(icon);
        pushButton_last->setIconSize(QSize(32, 32));
        pushButton_play = new QPushButton(groupBox_1);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        pushButton_play->setGeometry(QRect(130, 0, 41, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/play_on.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_play->setIcon(icon1);
        pushButton_play->setIconSize(QSize(43, 43));
        pushButton_play->setCheckable(false);
        pushButton_play->setChecked(false);
        pushButton_next = new QPushButton(groupBox_1);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));
        pushButton_next->setGeometry(QRect(190, 0, 41, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_next->setIcon(icon2);
        pushButton_next->setIconSize(QSize(32, 32));
        slider_voice = new QSlider(groupBox_1);
        slider_voice->setObjectName(QString::fromUtf8("slider_voice"));
        slider_voice->setGeometry(QRect(360, 13, 121, 16));
        slider_voice->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid #4A708B;\n"
"background: #C0C0C0;\n"
"height: 5px;\n"
"border-radius: 1px;\n"
"padding-left:-1px;\n"
"padding-right:-1px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \n"
"    stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #5DCCFF, stop: 1 #1874CD);\n"
"border: 1px solid #4A708B;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal {\n"
"background: #575757;\n"
"border: 0px solid #777;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal \n"
"{\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, \n"
"    stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:hover {\n"
"    backgrou"
                        "nd: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA, \n"
"    stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #00009C;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}\n"
"\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\n"
"\347\211\210\346\235\203\345\243\260\346\230\216\357\274\232\346\234\254\346\226\207\344\270\272CSDN\345\215\232\344\270\273\343\200\214DaGod123\343\200\215\347\232\204\345\216\237\345\210\233\346\226\207\347\253\240\357\274\214\351"
                        "\201\265\345\276\252CC 4.0 BY-SA\347\211\210\346\235\203\345\215\217\350\256\256\357\274\214\350\275\254\350\275\275\350\257\267\351\231\204\344\270\212\345\216\237\346\226\207\345\207\272\345\244\204\351\223\276\346\216\245\345\217\212\346\234\254\345\243\260\346\230\216\343\200\202\n"
"\345\216\237\346\226\207\351\223\276\346\216\245\357\274\232https://blog.csdn.net/fengzhongye51460/article/details/115747235"));
        slider_voice->setValue(99);
        slider_voice->setOrientation(Qt::Horizontal);
        pushButton_love = new QPushButton(groupBox_1);
        pushButton_love->setObjectName(QString::fromUtf8("pushButton_love"));
        pushButton_love->setGeometry(QRect(250, 0, 41, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/love_0.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_love->setIcon(icon3);
        pushButton_love->setIconSize(QSize(32, 32));
        pushButton_love->setCheckable(false);
        pushButton_love->setChecked(false);
        pushButton_voice = new QPushButton(groupBox_1);
        pushButton_voice->setObjectName(QString::fromUtf8("pushButton_voice"));
        pushButton_voice->setGeometry(QRect(330, 10, 21, 21));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/voice_on.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_voice->setIcon(icon4);
        pushButton_voice->setIconSize(QSize(24, 24));
        pushButton_voice->setCheckable(false);
        pushButton_voice->setChecked(false);
        pushButton_order = new QPushButton(groupBox_1);
        pushButton_order->setObjectName(QString::fromUtf8("pushButton_order"));
        pushButton_order->setGeometry(QRect(10, 0, 41, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/order_sequential.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_order->setIcon(icon5);
        pushButton_order->setIconSize(QSize(43, 43));
        pushButton_order->setCheckable(false);
        pushButton_order->setChecked(false);
        groupBox_2 = new QGroupBox(Console);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(800, 20, 190, 41));
        groupBox_2->setStyleSheet(QString::fromUtf8("border:none"));
        pushButton_speed = new QPushButton(groupBox_2);
        pushButton_speed->setObjectName(QString::fromUtf8("pushButton_speed"));
        pushButton_speed->setGeometry(QRect(50, 0, 41, 41));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/speed_1.0.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_speed->setIcon(icon6);
        pushButton_speed->setIconSize(QSize(32, 32));
        pushButton_upend = new QPushButton(groupBox_2);
        pushButton_upend->setObjectName(QString::fromUtf8("pushButton_upend"));
        pushButton_upend->setGeometry(QRect(100, 0, 41, 41));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/upend.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_upend->setIcon(icon7);
        pushButton_upend->setIconSize(QSize(32, 32));
        pushButton_set = new QPushButton(groupBox_2);
        pushButton_set->setObjectName(QString::fromUtf8("pushButton_set"));
        pushButton_set->setGeometry(QRect(150, 0, 41, 41));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/set.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_set->setIcon(icon8);
        pushButton_set->setIconSize(QSize(32, 32));
        pushButton_screen = new QPushButton(groupBox_2);
        pushButton_screen->setObjectName(QString::fromUtf8("pushButton_screen"));
        pushButton_screen->setGeometry(QRect(0, 0, 41, 41));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/screen_full.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_screen->setIcon(icon9);
        pushButton_screen->setIconSize(QSize(32, 32));
        slider_frame = new QSlider(Console);
        slider_frame->setObjectName(QString::fromUtf8("slider_frame"));
        slider_frame->setGeometry(QRect(0, 0, 1001, 20));
        slider_frame->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid #4A708B;\n"
"background: #C0C0C0;\n"
"height: 5px;\n"
"border-radius: 1px;\n"
"padding-left:-1px;\n"
"padding-right:-1px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \n"
"    stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #5DCCFF, stop: 1 #1874CD);\n"
"border: 1px solid #4A708B;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal {\n"
"background: #575757;\n"
"border: 0px solid #777;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal \n"
"{\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, \n"
"    stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:hover {\n"
"    backgrou"
                        "nd: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA, \n"
"    stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #00009C;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}\n"
""));
        slider_frame->setOrientation(Qt::Horizontal);
        QWidget::setTabOrder(pushButton_order, pushButton_last);
        QWidget::setTabOrder(pushButton_last, pushButton_play);
        QWidget::setTabOrder(pushButton_play, pushButton_next);
        QWidget::setTabOrder(pushButton_next, pushButton_love);
        QWidget::setTabOrder(pushButton_love, pushButton_voice);
        QWidget::setTabOrder(pushButton_voice, slider_voice);
        QWidget::setTabOrder(slider_voice, pushButton_speed);
        QWidget::setTabOrder(pushButton_speed, pushButton_upend);

        retranslateUi(Console);

        QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QWidget *Console)
    {
        Console->setWindowTitle(QCoreApplication::translate("Console", "Form", nullptr));
        groupBox_0->setTitle(QString());
        label_time->setText(QCoreApplication::translate("Console", "00:00:00 / 00:00:00", nullptr));
        groupBox_1->setTitle(QString());
        pushButton_last->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_last->setShortcut(QCoreApplication::translate("Console", "Ctrl+Left", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_play->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_play->setShortcut(QCoreApplication::translate("Console", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_next->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_next->setShortcut(QCoreApplication::translate("Console", "Ctrl+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_love->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_love->setShortcut(QCoreApplication::translate("Console", "Ctrl+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_voice->setText(QString());
        pushButton_order->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_order->setShortcut(QCoreApplication::translate("Console", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox_2->setTitle(QString());
        pushButton_speed->setText(QString());
        pushButton_upend->setText(QString());
        pushButton_set->setText(QString());
        pushButton_screen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_H
