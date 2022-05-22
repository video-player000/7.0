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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Console
{
public:
    QGroupBox *groupBox_0;
    QGroupBox *groupBox_1;
    QPushButton *pushButton_play;
    QPushButton *pushButton_next;
    QSlider *slider_voice;
    QPushButton *pushButton_voice;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_screen;
    QPushButton *pushButton_upend;
    QPushButton *pushButton_speed;
    QPushButton *pushButton_floder;
    QPushButton *pushButton_set;
    QSlider *slider_frame;
    QLabel *label_time;

    void setupUi(QWidget *Console)
    {
        if (Console->objectName().isEmpty())
            Console->setObjectName(QString::fromUtf8("Console"));
        Console->resize(1012, 69);
        QFont font;
        font.setStrikeOut(false);
        Console->setFont(font);
        Console->setFocusPolicy(Qt::StrongFocus);
        Console->setAutoFillBackground(false);
        Console->setStyleSheet(QString::fromUtf8(""));
        groupBox_0 = new QGroupBox(Console);
        groupBox_0->setObjectName(QString::fromUtf8("groupBox_0"));
        groupBox_0->setEnabled(true);
        groupBox_0->setGeometry(QRect(0, 10, 161, 41));
        groupBox_0->setFont(font);
        groupBox_0->setAutoFillBackground(false);
        groupBox_0->setStyleSheet(QString::fromUtf8("border:none"));
        groupBox_1 = new QGroupBox(Console);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        groupBox_1->setGeometry(QRect(0, 20, 291, 41));
        groupBox_1->setStyleSheet(QString::fromUtf8("border:none"));
        pushButton_play = new QPushButton(groupBox_1);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        pushButton_play->setGeometry(QRect(10, 0, 51, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/play_on.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_play->setIcon(icon);
        pushButton_play->setIconSize(QSize(28, 28));
        pushButton_play->setCheckable(false);
        pushButton_play->setChecked(false);
        pushButton_next = new QPushButton(groupBox_1);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));
        pushButton_next->setGeometry(QRect(60, 0, 41, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_next->setIcon(icon1);
        pushButton_next->setIconSize(QSize(30, 30));
        slider_voice = new QSlider(groupBox_1);
        slider_voice->setObjectName(QString::fromUtf8("slider_voice"));
        slider_voice->setGeometry(QRect(150, 10, 131, 16));
        slider_voice->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid #7a4d5f;\n"
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
"    stop: 0 #fc6984, stop: 1 #040f1b);\n"
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
"    stop:0.6 #7a4d5f, stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:hover {\n"
"    backgrou"
                        "nd: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #be6570, \n"
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
        slider_voice->setValue(99);
        slider_voice->setOrientation(Qt::Horizontal);
        pushButton_voice = new QPushButton(groupBox_1);
        pushButton_voice->setObjectName(QString::fromUtf8("pushButton_voice"));
        pushButton_voice->setGeometry(QRect(100, 0, 41, 41));
        QFont font1;
        font1.setPointSize(11);
        pushButton_voice->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/volume.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_voice->setIcon(icon2);
        pushButton_voice->setIconSize(QSize(30, 30));
        pushButton_voice->setCheckable(false);
        pushButton_voice->setChecked(false);
        groupBox_2 = new QGroupBox(Console);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(660, 20, 311, 50));
        groupBox_2->setFocusPolicy(Qt::NoFocus);
        groupBox_2->setStyleSheet(QString::fromUtf8("border:none"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/wall_paper.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);
        pushButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton);

        pushButton_screen = new QPushButton(groupBox_2);
        pushButton_screen->setObjectName(QString::fromUtf8("pushButton_screen"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/screen_full.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_screen->setIcon(icon4);
        pushButton_screen->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton_screen);

        pushButton_upend = new QPushButton(groupBox_2);
        pushButton_upend->setObjectName(QString::fromUtf8("pushButton_upend"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/upend.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_upend->setIcon(icon5);
        pushButton_upend->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton_upend);

        pushButton_speed = new QPushButton(groupBox_2);
        pushButton_speed->setObjectName(QString::fromUtf8("pushButton_speed"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/speed_1.0.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_speed->setIcon(icon6);
        pushButton_speed->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton_speed);

        pushButton_floder = new QPushButton(groupBox_2);
        pushButton_floder->setObjectName(QString::fromUtf8("pushButton_floder"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_floder->setIcon(icon7);
        pushButton_floder->setIconSize(QSize(31, 31));

        horizontalLayout->addWidget(pushButton_floder);

        pushButton_set = new QPushButton(groupBox_2);
        pushButton_set->setObjectName(QString::fromUtf8("pushButton_set"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/set.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_set->setIcon(icon8);
        pushButton_set->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton_set);

        slider_frame = new QSlider(Console);
        slider_frame->setObjectName(QString::fromUtf8("slider_frame"));
        slider_frame->setGeometry(QRect(160, 0, 781, 20));
        slider_frame->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid #7a4d5f;\n"
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
"    stop: 0 #fc6984, stop: 1 #040f1b);\n"
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
"    stop:0.6 #7a4d5f, stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:hover {\n"
"    backgrou"
                        "nd: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #be6570, \n"
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
        label_time = new QLabel(Console);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(20, 0, 131, 20));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font2.setPointSize(10);
        font2.setStrikeOut(false);
        label_time->setFont(font2);
        QWidget::setTabOrder(pushButton_play, pushButton_next);
        QWidget::setTabOrder(pushButton_next, pushButton_voice);
        QWidget::setTabOrder(pushButton_voice, slider_voice);
        QWidget::setTabOrder(slider_voice, pushButton_speed);

        retranslateUi(Console);

        QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QWidget *Console)
    {
        Console->setWindowTitle(QCoreApplication::translate("Console", "Form", nullptr));
        groupBox_0->setTitle(QString());
        groupBox_1->setTitle(QString());
        pushButton_play->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_play->setShortcut(QCoreApplication::translate("Console", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_next->setText(QString());
#if QT_CONFIG(shortcut)
        pushButton_next->setShortcut(QCoreApplication::translate("Console", "Ctrl+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_voice->setText(QString());
        groupBox_2->setTitle(QString());
        pushButton->setText(QString());
        pushButton_screen->setText(QString());
        pushButton_upend->setText(QString());
        pushButton_speed->setText(QString());
        pushButton_floder->setText(QString());
        pushButton_set->setText(QString());
        label_time->setText(QCoreApplication::translate("Console", "00:00:00 / 00:00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_H
