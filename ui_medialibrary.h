/********************************************************************************
** Form generated from reading UI file 'medialibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIALIBRARY_H
#define UI_MEDIALIBRARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Medialibrary
{
public:
    QGroupBox *groupBox;
    QPushButton *mediaButton;
    QPushButton *browingButton;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_1;
    QWidget *page_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;

    void setupUi(QWidget *Medialibrary)
    {
        if (Medialibrary->objectName().isEmpty())
            Medialibrary->setObjectName(QString::fromUtf8("Medialibrary"));
        Medialibrary->setWindowModality(Qt::NonModal);
        Medialibrary->setEnabled(true);
        Medialibrary->resize(365, 514);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Medialibrary->sizePolicy().hasHeightForWidth());
        Medialibrary->setSizePolicy(sizePolicy);
        Medialibrary->setLayoutDirection(Qt::LeftToRight);
        groupBox = new QGroupBox(Medialibrary);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 371, 61));
        groupBox->setStyleSheet(QString::fromUtf8("border:none"));
        mediaButton = new QPushButton(groupBox);
        mediaButton->setObjectName(QString::fromUtf8("mediaButton"));
        mediaButton->setGeometry(QRect(10, 10, 131, 71));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mediaButton->sizePolicy().hasHeightForWidth());
        mediaButton->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(22);
        font.setBold(false);
        mediaButton->setFont(font);
        mediaButton->setContextMenuPolicy(Qt::NoContextMenu);
        mediaButton->setStyleSheet(QString::fromUtf8("color:white"));
        browingButton = new QPushButton(groupBox);
        browingButton->setObjectName(QString::fromUtf8("browingButton"));
        browingButton->setGeometry(QRect(150, 14, 161, 61));
        sizePolicy1.setHeightForWidth(browingButton->sizePolicy().hasHeightForWidth());
        browingButton->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(22);
        font1.setBold(false);
        font1.setItalic(false);
        browingButton->setFont(font1);
        browingButton->setStyleSheet(QString::fromUtf8("color:white"));
        stackedWidget = new QStackedWidget(Medialibrary);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 70, 351, 431));
        stackedWidget->setStyleSheet(QString::fromUtf8("border:none"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setEnabled(true);
        page->setStyleSheet(QString::fromUtf8("border:none"));
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(page);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,0)"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_1 = new QWidget();
        scrollAreaWidgetContents_1->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_1"));
        scrollAreaWidgetContents_1->setGeometry(QRect(0, 0, 351, 431));
        scrollAreaWidgetContents_1->setFocusPolicy(Qt::NoFocus);
        scrollArea->setWidget(scrollAreaWidgetContents_1);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setAutoFillBackground(false);
        page_2->setStyleSheet(QString::fromUtf8(""));
        scrollArea_2 = new QScrollArea(page_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(-10, 10, 381, 441));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy2);
        scrollArea_2->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,0)"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 381, 441));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        stackedWidget->addWidget(page_2);

        retranslateUi(Medialibrary);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Medialibrary);
    } // setupUi

    void retranslateUi(QWidget *Medialibrary)
    {
        Medialibrary->setWindowTitle(QCoreApplication::translate("Medialibrary", "Widget", nullptr));
        mediaButton->setText(QCoreApplication::translate("Medialibrary", "Media", nullptr));
        browingButton->setText(QCoreApplication::translate("Medialibrary", "History", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Medialibrary: public Ui_Medialibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIALIBRARY_H
