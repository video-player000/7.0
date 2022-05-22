/********************************************************************************
** Form generated from reading UI file 'project_50.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_50_H
#define UI_PROJECT_50_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_project_50Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *project_50Class)
    {
        if (project_50Class->objectName().isEmpty())
            project_50Class->setObjectName(QString::fromUtf8("project_50Class"));
        project_50Class->resize(600, 400);
        menuBar = new QMenuBar(project_50Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        project_50Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(project_50Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        project_50Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(project_50Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        project_50Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(project_50Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        project_50Class->setStatusBar(statusBar);

        retranslateUi(project_50Class);

        QMetaObject::connectSlotsByName(project_50Class);
    } // setupUi

    void retranslateUi(QMainWindow *project_50Class)
    {
        project_50Class->setWindowTitle(QCoreApplication::translate("project_50Class", "project_50", nullptr));
    } // retranslateUi

};

namespace Ui {
    class project_50Class: public Ui_project_50Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_50_H
