#ifndef CONSOLE_H
#define CONSOLE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>


#include <QTimer>

namespace Ui {
class Console;
}

//底部控制台类

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();
    void console_init();
    void console_free();

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void console_hide();
    void console_show();

signals:
    void signal_console_console_resize(bool ishide);
    void signal_console_pause(bool pause);
    void signal_console_volume(int volume);
    void signal_console_seek(int64_t timestamp);
    void signal_console_seek_show(double position);
    void signal_console_seek_hide();
    void signal_console_skip();
    void signal_console_screen(bool turnfull);
    void signal_console_upend(double upend_speed);
    void signal_console_upend_cancel();
    void signal_medialibrary_show();
    void signal_window_close();
    void signal_media_floder_input();
    void signal_wall_paper_change();
    

private slots:
    void slot_hide_timer_timeout();

    //帧进度条
    void on_slider_frame_sliderPressed();
    void on_slider_frame_sliderMoved(int position);
    void on_slider_frame_sliderReleased();

    //播放顺序按钮
    //void on_pushButton_order_clicked();
    //上一首按钮
    void on_pushButton_last_clicked();
    //播放-暂停按钮
    void on_pushButton_play_toggled(bool checked);
    //下一首按钮
    void on_pushButton_next_clicked();
    //喜欢按钮
    //void on_pushButton_love_toggled(bool checked);

    //声音按钮
    void on_pushButton_voice_toggled(bool checked);
    //声音条
    void on_slider_voice_sliderPressed();
    void on_slider_voice_sliderReleased();
    void on_slider_voice_valueChanged(int value);

    //全屏-窗口按钮
    void on_pushButton_screen_clicked(bool checked);
    //倍速按钮
    void on_pushButton_speed_clicked();
    //倒放按钮
    void on_pushButton_upend_pressed();
    void slot_upend_timer_timeout();
    void on_pushButton_upend_released();
    //关闭按钮
    void on_pushButton_set_clicked();

    //导入文件夹
    void on_pushButton_floder_clicked();

    //切换壁纸
    void on_pushButton_clicked();

    void slot_console_resize(int width, int height);
    void slot_console_duration(double duration);
    void slot_console_clock(double clock);
    
    //全屏相关
    void slot_full_sreen_set(bool turnoff);
    
    
private:
    Ui::Console* ui;
    int mainwindow_width;
    int mainwindow_height;
    bool if_full_screen;
    const int console_height = 80;//固定
    const int console_hide_height = 20;//固定

    bool init;//是否完成初始化,只有完成后才能对控制台进行操控

    bool frame_ispressed;//判断用户是否按压帧进度条

    double duration;
    QString format_duration;
    double clock;
    int clock_format;//格式 "分:秒"-0 "时:分:秒"-1

    int order;//sequential-0 single-1 random-2
    int voice_value;//from 0 to 100

    bool ishide;
    bool hide_timer_on;
    QTimer* hide_timer;

    double speed;//0.5 1.0 2.0 4.0 8.0

    QTimer* upend_timer;
    bool upend_timer_on;
    int upend_state;

    bool media_open;
};
#endif 
