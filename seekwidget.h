#ifndef SEEKWIDGET_H
#define SEEKWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

//预览条显示类

class Seekwidget: public QWidget
{
    Q_OBJECT

public:
    explicit Seekwidget(QWidget* parent = nullptr);
    ~Seekwidget();
    void seekwidget_init();

public slots:
    void slot_seekwidget_resize(int width, int height);
    void slot_seekwidget_show(double position);
    void slot_seekwidget_hide();
    void slot_seekwidget_setimage(QImage t_image);
    void paintEvent(QPaintEvent* event);

private:
    int mainwindow_width;
    int mainwindow_height;
    const int console_height = 80;//固定
    int seekwidget_width;
    int seekwidget_height;
    QImage image;
};

#endif // SEEKWIDGET_H