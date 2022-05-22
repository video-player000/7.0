#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QStyle>
#include <QStyleOption>
#include "core.h"
#include "display.h"
#include "console.h"
#include "seekwidget.h"
#include "medialibrary.h"

//主窗口

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int wall_paper;
    int wall_papercount;
    QString file_path;
    QPoint last;
    Core* core;
    Display* display;
    Console* console;
    Seekwidget* seekwidget;
    Medialibrary* medialibrary;
    QLabel* selectfilename;
    QLabel* selectfileinfo;
    


public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void mainwindow_init(QString file_path);
    void resizeEvent(QResizeEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void core_init();//内核初始化(初始化/重新初始化)
    void core_free();//内核格式化
    void core_start();//内核启动
    void console_init();//控制台初始化(初始化/重新初始化)
    void console_free();//控制台格式化
    void display_init();
    void seekwidget_init();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent* p);

signals:
    void signal_mainwindow_resize(int width, int height);
    void signal_medialibrary_open(bool if_open);
    void signal_window_fullsreen(bool turnfull);


public slots:
    void slot_mainwindow_screen(bool turnfull);
    void slot_medialibrary_show();
    void slot_mediafile_clicked(QString filepath);
    void slot_wallpaper_change();
    
   
};
#endif // MAINWINDOW_H
