#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    if (argc == 2) {
        QString file_path = QString(argv[1]);
        mainwindow.mainwindow_init(file_path);
    }
  
    return a.exec();
}

//����

//����ᱼ�� thread_read��ֱ���˳�
