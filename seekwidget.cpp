#include "seekwidget.h"


Seekwidget::Seekwidget(QWidget* parent)
    : QWidget(parent)
{
    this->mainwindow_width = 0;
    this->mainwindow_height = 0;
    this->seekwidget_width = 0;
    this->seekwidget_height = 0;
    //this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    this->setVisible(0);
}

Seekwidget::~Seekwidget()
{

}

void Seekwidget::seekwidget_init()
{
    this->image = QImage();
}

void Seekwidget::slot_seekwidget_resize(int width, int height)
{
    this->mainwindow_width = width;
    this->mainwindow_height = height;

    this->seekwidget_width = width / 5;
    this->seekwidget_height = height / 5;
    this->resize(this->seekwidget_width, this->seekwidget_height);
}

void Seekwidget::slot_seekwidget_show(double position)
{
    
    int position_x = this->mainwindow_width * position;
    if (position_x < this->seekwidget_width / 2) {
        position_x = 0;
    }
    else if (position_x > this->mainwindow_width - this->seekwidget_width / 2) {
        position_x = this->mainwindow_width - this->seekwidget_width;
    }
    else
    {
        position_x -= this->seekwidget_width / 2;
    }
    this->setGeometry(position_x, this->mainwindow_height - this->seekwidget_height - this->console_height, this->seekwidget_width, this->seekwidget_height);
    this->setVisible(1);
}

void Seekwidget::slot_seekwidget_hide()
{
    this->setVisible(0);
}

void Seekwidget::slot_seekwidget_setimage(QImage image)
{
    this->image = image;
    update();
}

void Seekwidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());
    if (this->image.size().width() == 0) return;

    QPixmap img = QPixmap::fromImage(this->image.scaled(this->size(), Qt::KeepAspectRatio));
    int x = (this->width() - img.width()) / 2;
    int y = (this->height() - img.height()) / 2;
    painter.drawPixmap(x, y, img);
}
