#include "file.h"
#include <QDebug>
#include"io.h"
#include<string>
#include <iostream>
#include <vector>
#include <algorithm>


//获取初始文件夹中所有文件名与文件路径，包含子文件夹中的文件名和文件路径   可以考虑提前读取到数据库
void File::getFilesPath(string path)
{
    long long hFile = 0;
    struct _finddata_t fileinfo;
    string pathp;
    if ((hFile = _findfirst(pathp.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    //不获取子文件夹内文件
                    continue;
                    //获取子文件夹文件
                    //(pathp.assign(path).append("//").append(fileinfo.name));
                    
                }
            }
            else
            {
                string filestr = fileinfo.name;
                QString select = QString::fromStdString(filestr);
                if(select.contains(".mp4") || select.contains(".mp3")) 
                {
                    qDebug() << QString::fromStdString(filestr);
                    fileNamelist.push_back(filestr);
                    filePathlist.push_back(pathp.assign(path).append("\\").append(filestr));
                }
               
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}
File::File()
{
    initializeDatabase();
    createBrowingTable();
    loadingBrowingTable();

}

void File::loadData()
{
    getFilesPath(dirPath.toStdString());
    createDataBase();

}
//读取所有文件名到数据库

//从数据库读入所有文件名




//初始化数据库
void File::initializeDatabase()
{
    // 创建并打开数据库
    database = QSqlDatabase::addDatabase("QSQLITE");//将所使用的数据库驱动（如：QSQLITE）添加进来
    database.setDatabaseName("data.db"); //赋值所用数据库文件名称
    //打开数据库文件
    if(!database.open())
        qDebug() << "Error: Failed to connect  Database." << database.lastError();
    else
        qDebug() << "OK!";

    //将QSqlQuery操作语句与数据库绑定！
    sql_query=QSqlQuery(database);
}

//创建本地文件数据库表，并且导入本地文件数据
void File::createDataBase()
{

    // 重新构建表，此处先清空
    sql_query.exec("DROP TABLE allfile");

    // 创建表格allFile
    if(!sql_query.exec("create table allFile(Id int primary key, fileName text,filePath text)"))
        qDebug() << "Error: Fail to create allFile table." << sql_query.lastError();


    // 批量创建初始表
    sql_query.prepare("INSERT INTO allFile (Id, fileName,filePath) "
                      "VALUES (:Id, :fileName, :filePath)"); // 绑定关键字后才能进行操作 赋值语句
    for (unsigned long long i = 0; i < fileNamelist.size(); i++)
    {
        sql_query.bindValue(":Id", i); // 文件  ID
        sql_query.bindValue(":fileName", fileNamelist[i].c_str()); // 文件名
        sql_query.bindValue(":filePath", filePathlist[i].c_str()); // 文件路径
        if(!sql_query.exec())
            qDebug() << "Error:Create initial table Fail." << sql_query.lastError();
    }
}





//保存到数据库浏览记录
void File::saveChoosefile(string choosefile)
{
    browingHistory.push_back(choosefile);
    updateBrowingTable(choosefile);

}

//创建浏览记录表
void File::createBrowingTable()
{
    //如果表单不存在，则创建
    int flag=sql_query.exec(QString("select count(*) from browingHistory "));
    if(!flag)
    {
        qDebug()<<sql_query.value(0).toInt();
        if(sql_query.value(0).toInt()==0)
        {
            // 重新构建表，此处先清空
            sql_query.exec("DROP TABLE browingHistory");
            // 创建表格browingHistory
            if(!sql_query.exec("create table browingHistory(Id int primary key, fileName text,filePath text,fileExist bool)"))
                qDebug() << "Error: Fail to create allFile table." << sql_query.lastError();
        }
    }
}

//更新浏览记录表
void File::updateBrowingTable(string choosefile)
{
    int index=choosefile.find_last_of('\\');
    string fileName=choosefile.substr(index+1);//文件名
    string filePath=choosefile;//文件路径

    //判断是否存在
    int level=-1;
    sql_query.exec(QString("SELECT * from browingHistory WHERE fileName = '%1'").arg(fileName.c_str()));
    if(sql_query.next())
    {
            level = sql_query.value(0).toInt();
    }
    //若点击项存在则删去  序号还在，会自动补齐
    if (level!=-1)
    {
    sql_query.prepare(QString("Delete from browingHistory WHERE fileName = '%1'").arg(fileName.c_str()));
    if(!sql_query.exec())
        {
            qDebug() << "Error: Fail." << sql_query.lastError();
        }
    }
    //更新原来项的ID
    sql_query.exec("SELECT * FROM browingHistory;");
    vector<string> listAll;
    while (sql_query.next())
    {
        QString str_name=sql_query.value(1).toString();
        listAll.push_back(str_name.toStdString());
    }
    for (unsigned long i =0;i<listAll.size();i++)
    {
        sql_query.prepare(QString("UPDATE browingHistory SET Id = '%1' WHERE fileName = '%2'").arg(i).arg(listAll[i].c_str()));
            if(!sql_query.exec())
            {
                qDebug() << "Error: Fail." << sql_query.lastError();
            }
    }
    int ID=0;//文件ID
    sql_query.exec("SELECT * FROM browingHistory ;");
    while(sql_query.next())
        ID++;

    //若点击项不存在则插入末尾
    sql_query.prepare("INSERT INTO browingHistory(Id, fileName,filePath,fileExist) "
                      "VALUES (:Id, :fileName, :filePath,:fileExist)"); // 绑定关键字后才能进行操作 赋值语句
    sql_query.bindValue(":Id", ID); // 文件  ID
    sql_query.bindValue(":fileName", fileName.c_str()); // 文件名
    sql_query.bindValue(":filePath", filePath.c_str()); // 文件路径
    sql_query.bindValue(":fileExist", true); // 文件是否存在
    if(!sql_query.exec())
        qDebug() << "Error:Create initial table Fail." << sql_query.lastError();

    //重新赋值新的
    loadingBrowingTable();
}

//从浏览记录数据库用于初始化
void File::loadingBrowingTable()
{
    //查询表中的数据
    sql_query.exec("SELECT * FROM browingHistory;");
    //初始化变量
    historyNamelist.clear();
    historyPathlist.clear();
    while (sql_query.next())
    {
        QString str_name=sql_query.value(1).toString();
        historyNamelist.push_back(str_name.toStdString());
        QString str_path=sql_query.value(2).toString();
        historyPathlist.push_back(str_path.toStdString());
    }
    checkFileExist();

}

//用文件管理器打开文件夹
QString File::openExplorer(QWidget* par)
{
//用文件管理器打开文件夹
QString str = QFileDialog::getExistingDirectory(par,"文件浏览","/");
return str;
}


//查看浏览记录文件是否存在
void File::checkFileExist()
{
    for (unsigned long i=0;i<historyPathlist.size();i++)
    {
        QString strFile=historyPathlist[i].c_str();
        QFile tempFile(strFile);
        if(!tempFile.exists())
        {
            sql_query.prepare(QString("UPDATE browingHistory SET fileExist = false WHERE fileName = '%1'").arg(historyNamelist[i].c_str()));
            if(!sql_query.exec())
            {
                qDebug() << "Error: Fail." << sql_query.lastError();
            }
            historyExistlist.push_back(0);
        }
        else
        {
            historyExistlist.push_back(1);
        }
    }
}

