#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include "file.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <Qpainter>
#include <QFileInfo>
 #include<Qpainter>
#include <qdir.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Medialibrary; }
QT_END_NAMESPACE

//媒体库类

class Medialibrary : public QWidget
{
    Q_OBJECT
public:
    int m_iLabNum;
    int h_iLabNum;
    int mainwindow_width;
    int mainwindow_height;
    int media_image=0;
    bool if_open;
    const int medialibrary_width = 350;
    const int medialibrary_hide_height = 20;
    const int console_height = 80;
    const int console_hide_height = 20;
    File file;

public:
    Medialibrary(QWidget *parent = nullptr);
    ~Medialibrary();
    void mediaListdisplay();//媒体文件夹部分
    void BrowingHistorydisplay();//浏览历史部分
    void switchPage();
    void paintEvent(QPaintEvent* e);

signals:
    void signal_mediafile_clicked(QString file_path);


private slots:
    void MultiButtonClicked();
    void slot_media_floder_input();
    void slot_medialibrary_resize(int width, int height);

private:
    Ui::Medialibrary *ui;
};
#endif // MEDIALIBRARY_H
