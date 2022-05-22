#include "display.h"

Display::Display(QWidget *parent)
    : QWidget(parent)
{
    this->mainwindow_width = 0;
    this->mainwindow_height = 0;
    this->start_label = new QLabel(this);
    this->start_label->setGeometry(265, 165, 65, 65);

    ClickedState = 0; //初始化不点击 
    pQTimerSingleClicked = new QTimer(this); //新建定时器 
    connect(pQTimerSingleClicked, SIGNAL(timeout()), this, SLOT(timerSingleClick())); //关联定时器和槽函数
    
}

Display::~Display()
{

}

void Display::display_init()
{
    this->image = QImage();
    update();
}

void Display::slot_display_resize(int width, int height)
{
    this->mainwindow_width = width;
    this->mainwindow_height = height;
    if (width < 1100) 
    {
        this->setGeometry(30, 30, width * 3 / 5, height * 3 / 5);
        this->start_label->setGeometry(265, 165, 65, 65);
    }
    else
    {
        this->setGeometry(0, 0, width, height);
        this->start_label->setGeometry(width / 2-50, height / 2-50, 80, 80);
    }
    
}


void Display::slot_display_setimage(QImage image)
{
    this->image = image;
    update();//立即刷新绘图
}

//绘图事件
void Display::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());
    if (this->image.size().width() == 0) return;

    QPixmap img = QPixmap::fromImage(this->image.scaled(this->size(), Qt::KeepAspectRatio));
    int x = (this->width() - img.width())/2;
    int y = (this->height() - img.height())/2;
    painter.drawPixmap(x, y, img);
}

//视频中央的播放图标显示
void Display::slot_start_turn(bool checked)
{
    if (checked == true) {//现在正在播放,显示"暂停播放"的图标

        QImage img = QImage(":/icon/start_play.png");
        this->start_label->setPixmap(QPixmap::fromImage(img));
        this->start_label->setScaledContents(true); 
        this->start_label->show();
       
    }
    else {
        this->start_label->hide();
    }
}

//用于判断双击
void Display::mousePressEvent(QMouseEvent* e) {
    if (e->button() & Qt::LeftButton) {
        ClickedState++;
        
        if (ClickedState == 1)
        {
            pQTimerSingleClicked->start(330); //330ms判断双击间隔
            openchecked = !openchecked;
            
        }
        if (ClickedState == 2)
        {
            ClickedState = 0; //初始化
            pQTimerSingleClicked->stop(); //停止定时器继续计时
            fullscreenchecked = !fullscreenchecked;
            //按钮双击响应代码放这里
            emit signal_display_screen(fullscreenchecked);
            
            
        }
        
    }
    click = 1;
}

//双击定时器
void Display::timerSingleClick()
{
    ClickedState = 0; //初始化
    pQTimerSingleClicked->stop(); //定时器停止计时
    emit signal_display_pause(openchecked);
}


//void Display::slot_display_console_resize(bool ishide)
//{
//    if (ishide) {
//        this->setGeometry(30, 30, this->mainwindow_width * 3 / 5, this->mainwindow_height * 2 / 3);
//    }
//    else {
//        this->setGeometry(30, 30, this->mainwindow_width * 3 / 5, this->mainwindow_height * 2 / 3);
//    }
//}

//void Display::slot_display_resize_media(bool if_open)
//{
//    if (if_open) {
//        this->setGeometry(0, 0, this->mainwindow_width*3/4, this->mainwindow_height - this->console_height);
//        update();
//    }
//    else {
//        this->setGeometry(0, 0, this->mainwindow_width, this->mainwindow_height - this->console_height);
//        update();
//    }
//}