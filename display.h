#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>

//展示类

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = nullptr);
    ~Display();
    void display_init();
    void mousePressEvent(QMouseEvent* e);

public slots:
    void slot_display_resize(int width, int height);
    void slot_display_setimage(QImage image);
    void paintEvent(QPaintEvent* event);
    void slot_start_turn(bool checked);
    void timerSingleClick(); 
    //void slot_display_resize_media(bool if_open);
    

private:
    int mainwindow_width;
    int mainwindow_height;
    const int console_height = 80;
    const int console_hide_height = 20;
    int ClickedState; 
    int click = 0;
    bool openchecked=false;
    bool fullscreenchecked=false;
    QTimer* pQTimerSingleClicked; 
    QImage image;
    QLabel* start_label;

signals:
    void signal_display_pause(bool openchecked);
    void signal_display_screen(bool fullscreenchecked);

    
};
#endif // DISPLAY_H
