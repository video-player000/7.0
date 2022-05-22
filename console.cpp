#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
    //console.ui中的各组件的位置可以根据实际进行适应性调整
    this->mainwindow_width = 0;
    this->mainwindow_height = 0;
    this->init = false;

    this->frame_ispressed = false;
    ui->slider_frame->setPageStep(1);
    
    this->duration = 0;
    this->clock = 0;
    this->clock_format = 1;
    ui->label_time->setAlignment(Qt::AlignVCenter);
    ui->label_time->setStyleSheet("color: white");

    this->order = 0;
    if_full_screen = false;

    this->media_open = true;

    ui->pushButton_play->setCheckable(true);
    ui->pushButton_play->setChecked(false);//(操作)true:正在播放-暂停图标(现); false:正在暂停-播放图标(现)
    //setChecked()函数设置值在一开始是为false
    //之后每一次触发后,值都会被置反,然后调用相应的槽函数

    //ui->pushButton_love->setCheckable(true);
    //ui->pushButton_love->setChecked(false);//(状态)true:喜欢图标; false:不喜欢图标

    ui->pushButton_voice->setCheckable(true);
    ui->pushButton_voice->setChecked(true);//(状态)true:音量开图标; false:音量关图标

    this->voice_value = 100;
    ui->slider_voice->setPageStep(1);
    ui->slider_voice->setValue(100);

    this->ishide = false; 
    this->hide_timer_on = false;
    this->hide_timer = new QTimer(this);
    connect(this->hide_timer, SIGNAL(timeout()), this, SLOT(slot_hide_timer_timeout()));
    ui->pushButton_screen->setCheckable(true);
    ui->pushButton_screen->setChecked(false);//true:现在是全屏化-窗口化图标(现); (操作)false:现在是窗口化-全屏化图标(现)

    this->upend_timer = new QTimer(this);
    this->upend_timer_on = false;
    this->upend_state = 0;
    connect(this->upend_timer, SIGNAL(timeout()), this, SLOT(slot_upend_timer_timeout()));

    this->speed = 1.0;
}

void Console::console_init()
{
    this->init = true;
    ui->slider_frame->setValue(0);
    ui->pushButton_play->setChecked(false);
    /*ui->pushButton_love->setChecked(false);*/
    QIcon icon;
    icon.addFile(":/icon/speed_1.0.png");
    ui->pushButton_speed->setIcon(icon);
    this->speed = 1.0;

    this->hide_timer->start(5000);//改成不隐藏
    this->hide_timer_on = false;
}

void Console::console_free()
{
    this->voice_value = 100;
    ui->slider_voice->setValue(100);
    this->init = false;
}

void Console::enterEvent(QEnterEvent* event)
{
    if (!init) return;
    if (this->hide_timer_on) {
        this->hide_timer->stop();
    }
    if (!this->ishide) return;//控制台没有隐藏
    //控制台隐藏了
    console_show();
}

void Console::leaveEvent(QEvent* event)
{
    if (!init) return;
    if (this->hide_timer_on) {
        this->hide_timer->stop();
    }
    else {
        this->hide_timer_on = true;
    }
    hide_timer->start(5000);
}

void Console::slot_full_sreen_set(bool turnoff)
{
    if_full_screen = !if_full_screen;
    qDebug() << if_full_screen;
}

void Console::slot_hide_timer_timeout()
{
    this->hide_timer->stop();
    //qDebug() << if_full_screen;
    if (if_full_screen)
    {
        console_hide();
    }
    
}

void Console::console_hide()
{
    this->setGeometry(0, this->mainwindow_height - this->console_hide_height, this->mainwindow_width, this->console_hide_height);
    ui->slider_frame->setGeometry(0, 0, this->mainwindow_width, 20);
    this->ishide = true;
    emit signal_console_console_resize(true);
}

void Console::console_show()
{
    int width = mainwindow_width;
    int height = mainwindow_height;
    if (width > 1100)
    {
        this->setGeometry(0, height - this->console_height, width, this->console_height);
        int interval = (width - 160 - 500 - 190) / 2.5;
        ui->slider_frame->setGeometry(150, 0, width - 220, 20);
        ui->groupBox_0->setGeometry(0, 20, 160, 40);
        ui->groupBox_1->setGeometry(0, 22, 500, 40);
        ui->groupBox_2->setGeometry(700 + 2 * interval, 15, 250, 50);
    }
    else
    {
        this->setGeometry(0, height - this->console_height, width, this->console_height);
        int interval = (width - 160 - 500 - 190) / 2.5;
        ui->slider_frame->setGeometry(150, 0, width - 220, 20);
        ui->groupBox_0->setGeometry(0, 20, 160, 40);
        ui->groupBox_1->setGeometry(0, 22, 500, 40);
        ui->groupBox_2->setGeometry(600 + 2 * interval, 15, 250, 50);
    }
    this->ishide = false;
    emit signal_console_console_resize(false);
}

Console::~Console()
{
    delete ui;
}
//帧进度条
void Console::on_slider_frame_sliderPressed()
{
    if (!init) return;
    this->frame_ispressed = true;
}

void Console::on_slider_frame_sliderMoved(int position)
{
    if (!init) {
        ui->slider_frame->setValue(0);
        return;
    }
    emit signal_console_seek_show(double(position) / this->duration);
    emit signal_console_seek(int64_t(position));
}

void Console::on_slider_frame_sliderReleased()
{
    if (!init) return;
    emit signal_console_seek_hide();
    emit signal_console_skip();
    this->frame_ispressed = false;
}

//groupBox_1
//void Console::on_pushButton_order_clicked()
//{
//    if (!init) return;
//    if (this->order == 0) {
//        QIcon icon;
//        icon.addFile(":/icon/order_random.png");
//        ui->pushButton_order->setIcon(icon);
//    }
//    else if (this->order == 1) {
//        QIcon icon;
//        icon.addFile(":/icon/order_single.png");
//        ui->pushButton_order->setIcon(icon);
//    }
//    else {
//        QIcon icon;
//        icon.addFile(":/icon/order_sequential.png");
//        ui->pushButton_order->setIcon(icon);
//    }
//    this->order = (this->order + 1) % 3;
//}

void Console::on_pushButton_last_clicked()
{
    if (!init) return;
}

void Console::on_pushButton_play_toggled(bool checked)
{
    //checked标识:是否正在播放
    if (!init) return;
    if(checked == true) {//现在正在播放,显示"暂停播放"的图标
        QIcon icon;
        icon.addFile(":/icon/play_off.png");
        ui->pushButton_play->setIcon(icon);
    }
    else {
        QIcon icon;
        icon.addFile(":/icon/play_on.png");
        ui->pushButton_play->setIcon(icon);
    }
    emit signal_console_pause(!checked);
}

void Console::on_pushButton_next_clicked()
{
    if (!init) return;
}

//void Console::on_pushButton_love_toggled(bool checked)
//{
//    //checked标识:是否喜欢
//    if (!init) return;
//    if(checked == true) {
//        QIcon icon;
//        icon.addFile(":/icon/love_1.png");
//        ui->pushButton_love->setIcon(icon);
//
//    }
//    else {
//        QIcon icon;
//        icon.addFile(":/icon/love_0.png");
//        ui->pushButton_love->setIcon(icon);
//    }
//}

void Console::on_pushButton_voice_toggled(bool checked)
{
    if (!init) return;
    if(checked == true) {
        QIcon icon;
        icon.addFile(":/icon/volume.png");
        ui->pushButton_voice->setIcon(icon);
        ui->slider_voice->setValue(this->voice_value);
        emit signal_console_volume(this->voice_value);
    }
    else {
        QIcon icon;
        icon.addFile(":/icon/voice_off.png");
        ui->pushButton_voice->setIcon(icon);
        ui->slider_voice->setValue(0);
        emit signal_console_volume(0);
    }
}

void Console::on_slider_voice_sliderPressed()
{
    if (!init) return;
    this->voice_value = ui->slider_voice->value();
}

void Console::on_slider_voice_sliderReleased()
{
    if (!init) return;
    int voice_value_now = ui->slider_voice->value();
    if (this->voice_value == voice_value_now) {
        return;
    }
    else if (this->voice_value != 0 and voice_value_now != 0) {
        this->voice_value = voice_value_now;
        emit signal_console_volume(this->voice_value);
    }
    else if(this->voice_value == 0) {// 现在不为0
        this->voice_value = voice_value_now;
        ui->pushButton_voice->setChecked(true);
    }
    else {// voice_value_now == 0, 即现在为0
        ui->pushButton_voice->setChecked(false);
    }
}

void Console::on_slider_voice_valueChanged(int value)
{
    if (!init) {
        ui->slider_voice->setValue(100);
        return;
    }
    emit signal_console_volume(value);
}

//groupBox_2
void Console::on_pushButton_screen_clicked(bool checked)
{
    if (!init) return;
    if(checked == true) {//现在是全屏,显示"变成窗口"的图标
        QIcon icon;
        icon.addFile(":/icon/screen_window.png");
        ui->pushButton_screen->setIcon(icon);
    }
    else {
        QIcon icon;
        icon.addFile(":/icon/screen_full.png");
        ui->pushButton_screen->setIcon(icon);
    }
    emit signal_console_screen(checked);
}

void Console::on_pushButton_speed_clicked()
{
    if (!init) return;
    if (this->speed == 1.0) {
        QIcon icon;
        icon.addFile(":/icon/speed_1.2.png");
        ui->pushButton_speed->setIcon(icon);
        this->speed = 1.2;
    }
    else if (this->speed == 1.2) {
        QIcon icon;
        icon.addFile(":/icon/speed_1.5.png");
        ui->pushButton_speed->setIcon(icon);
        this->speed = 1.5;
    }
    else if(this->speed == 1.5) {
        QIcon icon;
        icon.addFile(":/icon/speed_2.0.png");
        ui->pushButton_speed->setIcon(icon);
        this->speed = 2.0;
    }
    else if(this->speed == 2.0) {
        QIcon icon;
        icon.addFile(":/icon/speed_0.5.png");
        ui->pushButton_speed->setIcon(icon);
        this->speed = 0.5;
    }
    else {
        QIcon icon;
        icon.addFile(":/icon/speed_1.0.png");
        ui->pushButton_speed->setIcon(icon);
        this->speed = 1.0;
    }
}

void Console::on_pushButton_upend_pressed()
{
    if (!init) return;
    if (this->upend_state == 0) {
        this->upend_timer_on = true;
        this->upend_timer->start(300);
    }
    else if (this->upend_state == 1) {
        this->upend_state = 0;
        this->upend_timer->stop();
        this->upend_timer_on = false;
        emit signal_console_upend(2.0);
    }
}

void Console::slot_upend_timer_timeout()
{
    this->upend_timer->stop();
    if (this->upend_state == 0) {
        this->upend_timer_on = false;
        emit signal_console_upend(1.0);
    }
    else {
        //do nothing
    }
}

void Console::on_pushButton_upend_released()
{
    if (!init) return;
    if (this->upend_timer_on) {
        this->upend_state = 1;
    }
    else {
        emit signal_console_upend_cancel();
    }
}

void Console::on_pushButton_set_clicked()
{
    emit signal_window_close();
}


void Console::slot_console_resize(int width, int height)
{
    this->mainwindow_width = width;
    this->mainwindow_height = height;
    if (width > 1100)
    {
        this->setGeometry(0, height - this->console_height, width, this->console_height);
        int interval = (width - 160 - 500 - 190) / 2.5;
        ui->slider_frame->setGeometry(150, 0, width - 220, 20);
        ui->groupBox_0->setGeometry(0, 20, 160, 40);
        ui->groupBox_1->setGeometry(0, 22, 500, 40);
        ui->groupBox_2->setGeometry(700 + 2 * interval, 15, 250, 50);
    }
    else
    {
        this->setGeometry(0, height - this->console_height, width, this->console_height);
        int interval = (width - 160 - 500 - 190) / 2.5;
        ui->slider_frame->setGeometry(150, 0, width - 220, 20);
        ui->groupBox_0->setGeometry(0, 20, 160, 40);
        ui->groupBox_1->setGeometry(0, 22, 500, 40);
        ui->groupBox_2->setGeometry(600 + 2 * interval, 15, 250, 50);
    }
    
}

void Console::slot_console_duration(double duration)
{
    this->duration = duration;
    int time = int(duration);
    if (duration < 3600) {
        clock_format = 0;
        int second = time % 60;
        int minute = (int)(time / 60);
        this->format_duration = QString("%1:%2")
            .arg(minute, 2, 10, QLatin1Char('0'))
            .arg(second, 2, 10, QLatin1Char('0'));
        ui->label_time->setText("00:00 / " + this->format_duration);
    }
    else {
        clock_format = 1;
        int second = time % 60;
        int minute = (int)(time / 60) % 60;
        int hour = (int)(time / 3600);
        this->format_duration = QString("%1:%2:%3")
            .arg(hour, 2, 10, QLatin1Char('0'))
            .arg(minute, 2, 10, QLatin1Char('0'))
            .arg(second, 2, 10, QLatin1Char('0'));
        ui->label_time->setText("00:00:00 / " + this->format_duration);
    }
    ui->slider_frame->setRange(0, time);
}

void Console::slot_console_clock(double clock)
{
    if (clock < 0) return;
    int time = int(clock);
    if (clock_format == 0) {
        int second = time % 60;
        int minute = (int)(time / 60);
        QString format_clock = QString("%1:%2")
            .arg(minute, 2, 10, QLatin1Char('0'))
            .arg(second, 2, 10, QLatin1Char('0'));
        ui->label_time->setText(format_clock + " / " + this->format_duration);
    }
    else if (clock_format == 1) {
        int minute = time % 60;
        int second = (int)(time / 60);
        int hour = (int)(time / 3600);
        QString format_clock = QString("%1:%2:%3")
            .arg(hour, 2, 10, QLatin1Char('0'))
            .arg(minute, 2, 10, QLatin1Char('0'))
            .arg(second, 2, 10, QLatin1Char('0'));
        ui->label_time->setText(format_clock + " / " + this->format_duration);
    }
    if (!this->frame_ispressed) {
        ui->slider_frame->setValue(time);
    }
}


//void Console::on_pushButton_media_clicked()
//{
//    emit signal_medialibrary_show();
//}


//void Console::on_pushButton_media_clicked(bool checked)
//{
//    emit signal_medialibrary_show();
//    if (!this->media_open) {//现在正在播放,显示"暂停播放"的图标
//        QIcon icon;
//        icon.addFile(":/icon/media_close.png");
//        ui->pushButton_media->setIcon(icon);
//    }
//    else {
//        QIcon icon;
//        icon.addFile(":/icon/media_open.png");
//        ui->pushButton_media->setIcon(icon);
//    }
//    this->media_open = !this->media_open;
//}


void Console::on_pushButton_floder_clicked()
{
    emit signal_media_floder_input();
}


void Console::on_pushButton_clicked()
{
    emit signal_wall_paper_change();
}

