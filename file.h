#ifndef FILE_H
#define FILE_H
#include"io.h"
#include<string>
#include <iostream>
#include <vector>
#include <QDebug>
#include <algorithm>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <qdir.h>
#include <QProcess>
#include <QFileDialog>

//文件相关类

using namespace std;

class File
{
public:
    QString dirPath;
    vector<string> fileNamelist;
    vector<string> filePathlist;
    vector<string> historyNamelist;
    vector<string> historyPathlist;
    vector<int> historyExistlist;
    vector<string> browingHistory;
    QSqlDatabase database;
    QSqlQuery sql_query;
   
public:
    File();
    void loadData();
    void getFilesPath(string path);
    void saveChoosefile(string choosefile);
    void initializeDatabase();
    void createDataBase();
    void createBrowingTable();
    void updateBrowingTable(string choosefile);
    void loadingBrowingTable();
    void checkFileExist();
    QString openExplorer(QWidget* par);
    

};

#endif // FILE_H

