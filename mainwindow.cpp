#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    wall_paper = 5; //第一张显示的图
    wall_papercount = 10;//壁纸数量-1
    this->setMinimumSize(1020,645);
    this->core = new Core();
    this->display = new Display(this);
    this->console = new Console(this);
    this->seekwidget = new Seekwidget(this);
    this->medialibrary = new Medialibrary(this);
    this->selectfilename = new QLabel(this);
    this->selectfileinfo = new QLabel(this);

    this->setAcceptDrops(true);
    this->setWindowFlags(Qt::FramelessWindowHint);//取消标题栏
    this->setObjectName("mainWindow");
    QString url = QString("#mainWindow{border-image:url(:/icon/background%1.jpg);}").arg(wall_paper);
    this->setStyleSheet(url);
   
     //emit signal_mainwindow_resize(this->width(), this->height());

    connect(this, SIGNAL(signal_mainwindow_resize(int, int)), this->display, SLOT(slot_display_resize(int, int)));
    connect(this, SIGNAL(signal_mainwindow_resize(int, int)), this->console, SLOT(slot_console_resize(int, int)));
    connect(this, SIGNAL(signal_mainwindow_resize(int, int)), this->seekwidget, SLOT(slot_seekwidget_resize(int, int)));
    connect(this, SIGNAL(signal_mainwindow_resize(int, int)), this->medialibrary, SLOT(slot_medialibrary_resize(int, int)));
    connect(this, SIGNAL(signal_medialibrary_open(bool)), this, SLOT(slot_mainwindow_screen(bool)));
    connect(this, SIGNAL(signal_window_fullsreen(bool)), this->console, SLOT(slot_full_sreen_set(bool)));
    connect(this->core, SIGNAL(signal_core_duration(double)), this->console, SLOT(slot_console_duration(double)));
    connect(this->core, SIGNAL(signal_core_getimage_display(QImage)), this->display, SLOT(slot_display_setimage(QImage)));
    connect(this->core, SIGNAL(signal_core_clock(double)), this->console, SLOT(slot_console_clock(double)));
    connect(this->core, SIGNAL(signal_core_getimage_seekwidget(QImage)), this->seekwidget, SLOT(slot_seekwidget_setimage(QImage)));

    connect(this->console, SIGNAL(signal_console_screen(bool)), this, SLOT(slot_mainwindow_screen(bool)));
    connect(this->console, SIGNAL(signal_console_pause(bool)), this->core, SLOT(slot_core_pause(bool)));
    connect(this->console, SIGNAL(signal_console_pause(bool)), this->display, SLOT(slot_start_turn(bool)));
    connect(this->console, SIGNAL(signal_console_volume(int)), this->core, SLOT(slot_core_volume(int)));
    connect(this->console, SIGNAL(signal_console_seek(int64_t)), this->core, SLOT(slot_core_seek(int64_t)));
    connect(this->console, SIGNAL(signal_console_skip()), this->core, SLOT(slot_core_skip()));
    connect(this->console, SIGNAL(signal_console_upend(double)), this->core, SLOT(slot_core_upend(double)));
    connect(this->console, SIGNAL(signal_console_upend_cancel()), this->core, SLOT(slot_core_upend_cancel()));

    connect(this->console, SIGNAL(signal_console_seek_show(double)), this->seekwidget, SLOT(slot_seekwidget_show(double)));
    connect(this->console, SIGNAL(signal_console_seek_hide()), this->seekwidget, SLOT(slot_seekwidget_hide()));

    connect(this->console, SIGNAL(signal_medialibrary_show()), this, SLOT(slot_medialibrary_show()));
    connect(this->console, SIGNAL(signal_window_close()), this, SLOT(close()));
    connect(this->console, SIGNAL(signal_media_floder_input()), this->medialibrary, SLOT(slot_media_floder_input()));
    connect(this->console, SIGNAL(signal_wall_paper_change()), this, SLOT(slot_wallpaper_change()));

    connect(this->display, SIGNAL(signal_display_pause(bool)), this->console, SLOT(on_pushButton_play_toggled(bool)));
    connect(this->display, SIGNAL(signal_display_screen(bool)), this, SLOT(slot_mainwindow_screen(bool)));
    connect(this->medialibrary, SIGNAL(signal_mediafile_clicked(QString)), this, SLOT(slot_mediafile_clicked(QString)));
    

}


MainWindow::~MainWindow()
{

}

void MainWindow::mainwindow_init(QString file_path)
{
    this->file_path = file_path;
    core_init();
    console_init();
    display_init();
    seekwidget_init();
    core_start();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    emit signal_mainwindow_resize(this->width(), this->height());
    
}


void MainWindow::mousePressEvent(QMouseEvent* event)//窗口拖拽事件
{

    last = event->globalPos();
    qDebug() << QString("%1,%2").arg(event->x()).arg(event->y());

}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->y() < 30) //仅限于界面上区域
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        move(x() + dx, y() + dy);
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->y() < 30) //仅限于界面上区域
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        move(x() + dx, y() + dy);
    }
}
void MainWindow::dragEnterEvent(QDragEnterEvent* event)//文件拖拽播放事件
{
    const QString filename = event->mimeData()->urls()[0].fileName();
    if (!filename.right(3).compare("mp4") || !filename.right(3).compare("mp3")) {//后缀名为.mp4或.mp3的文件
        event->acceptProposedAction();
    } 
    else {//否则不接受鼠标事件
        event->ignore();
    }  
}

void MainWindow::dropEvent(QDropEvent* event)//文件放下事件
{
    QList<QUrl> urls = event->mimeData()->urls();
    QStringList files;
    //接受的拖拽格式
    QString suffixs = "mp3 MP3 mp4 avi mkv mpg wmv webm rm rmvb mov flv ";
    //可以接受批量的拖入
    for( QUrl url : urls ){
        QFileInfo file(url.toLocalFile());	//toLocalFile可以获取文件路径，而非QUrl的file://开头的路径
        if (file.isFile() && suffixs.contains(file.suffix())) //过滤掉目录和不支持的后缀，如果要支持目录，则要自己遍历每一个目录。
            files.append(file.filePath());
    }

    if(!files.isEmpty())
    {
        for(int i =0;i<files.size();i++)
        {
            QString file1_path = QDir::toNativeSeparators(files[i]);//转为反斜杠
            medialibrary->file.saveChoosefile(file1_path.toStdString());
            medialibrary->BrowingHistorydisplay();
        }

    }
    file_path = QDir::toNativeSeparators(files[0]);//转为反斜杠

    slot_mediafile_clicked(file_path);

}

void MainWindow::core_init()
{
    if (core->core_init(this->file_path) != 0) {
        qDebug() << "Initialize process core-failed";
    }
}

void MainWindow::core_free()
{
    core->core_free();
}

void MainWindow::core_start()
{
    core->start();
}

void MainWindow::console_init()
{
    console->console_init();
}


void MainWindow::console_free()
{
    console->console_free();
}

void MainWindow::display_init()
{
    display->display_init();
}

void MainWindow::seekwidget_init()
{
    seekwidget->seekwidget_init();
}

void MainWindow::slot_mainwindow_screen(bool turnfull)
{
    if (turnfull) {//变为全屏
        this->showFullScreen();
        this->selectfilename->hide();
        this->selectfileinfo->hide();
    }
    else {//变为窗口
        this->showNormal();
        this->selectfilename->show();
        this->selectfileinfo->show();
    }
    emit signal_window_fullsreen(turnfull);
    emit signal_mainwindow_resize(this->width(), this->height());
}

void MainWindow::slot_medialibrary_show()
{
    if (this->medialibrary->if_open)
    {
        this->medialibrary->hide();
        this->medialibrary->if_open = false;
    }
    else
    {
        this->medialibrary->show();
        this->medialibrary->if_open = true;
    }
    emit signal_medialibrary_open(this->medialibrary->if_open);
    
}


void MainWindow::slot_mediafile_clicked(QString filepath)//接受媒体库点击事件并且播放视频
{
 
    //绘制左下角视频标题于信息
    file_path = filepath;
    QStringList file = file_path.split("\\");
    QStringList filelist = file.last().split(".");
    qDebug() << filelist[1];
    QString filename = filelist[0];
    for (int i = 1; i < filename.length() / 49 + 1; i++)
    {
        filename.insert(49 * i, QString("\n"));
    }
    this->selectfilename->setText(filename);
    this->selectfileinfo->setText(filelist[1]);
    int height = 410;
    this->selectfilename->setGeometry(30, height, 630, 100);
    this->selectfilename->show();
    this->selectfilename->setStyleSheet("text-align: left;font-size:25px;color:white");
    this->selectfileinfo->setGeometry(30, 465, 615, 100);
    this->selectfileinfo->show();
    this->selectfileinfo->setStyleSheet("text-align: left;font-size:18px;color:gray");
    

    //后续的播放操作
    core_init();
    console_init();
    display_init();
    seekwidget_init();
    core_start();
}


void MainWindow::paintEvent(QPaintEvent* p1)//绘制圆角
{
    //绘制样式
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);//绘制样式

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter painter(&bmp);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(bmp.rect(), 12, 12);
    setMask(bmp);
}

void MainWindow::slot_wallpaper_change()//更改壁纸
{
    wall_paper++;
    wall_paper = wall_paper % wall_papercount;
    this->setObjectName("mainWindow");
    QString url = QString("#mainWindow{border-image:url(:/icon/background%1.jpg);}").arg(wall_paper);
    this->setStyleSheet(url);
    this->show();

}