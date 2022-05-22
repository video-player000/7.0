#include "medialibrary.h"
#include "ui_medialibrary.h"

Medialibrary::Medialibrary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Medialibrary)
{
    m_iLabNum=0;
    h_iLabNum=0;
    if_open = false;
    ui->setupUi(this);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->mediaButton, &QPushButton::clicked, this, &Medialibrary::switchPage);
    connect(ui->browingButton, &QPushButton::clicked, this, &Medialibrary::switchPage);
    
    BrowingHistorydisplay();

    //立即播放最近第一首 未能实现
    //QString firstfile = file.historyPathlist[file.historyNamelist.size() - 1].c_str();
    //qDebug() << firstfile;
    //emit signal_mediafile_clicked(firstfile);
    
    

}

Medialibrary::~Medialibrary()
{

    delete ui;
}


//媒体文件夹部分
void Medialibrary::mediaListdisplay()
{
    m_iLabNum = 0;
    qDeleteAll(ui->scrollAreaWidgetContents_1->findChildren<QGroupBox*>());
    qDeleteAll(ui->scrollAreaWidgetContents_1->findChildren<QLabel*>());
    qDeleteAll(ui->scrollAreaWidgetContents_1->findChildren<QPushButton*>());
    //生成按钮
    for (unsigned long long i=0; i < file.fileNamelist.size(); i++)
    {
        QString str = file.fileNamelist[i].c_str();
        QStringList strlist = str.split(".");//QString字符串分割函数
        QString name = QString("%1：").arg(m_iLabNum);
        QString filename = QString("%1").arg(strlist[0]);
        for (int i = 1; i < filename.length() / 25 + 1; i++)
        {
            filename.insert(25 * i, QString("\n"));
        }

        QGroupBox* group = new QGroupBox(ui->scrollAreaWidgetContents_1);//创建组
        QLabel* label = new QLabel;
        QLabel* image = new QLabel;
 
        QString image_Path = QString(":/icon/image%1.jpg").arg(media_image%5);
        QImage img = QImage(image_Path);
        image->setPixmap(QPixmap::fromImage(img));
        image->setScaledContents(true);
        image->setFixedSize(180, 63);

        label->setText(strlist[1]);
        label->setStyleSheet("text-align: right;font-size:15px;color:gray");

        QPushButton* button = new QPushButton(ui->scrollAreaWidgetContents_1);//创建按钮
        QGridLayout* GLayout_0 = new QGridLayout;
        GLayout_0->addWidget(image, 0, 0, 2, 1);
        GLayout_0->addWidget(button, 0, 1);
        GLayout_0->addWidget(label, 1, 1);
        group->setLayout(GLayout_0);
        group->setGeometry(QRect(30, m_iLabNum * 120, 340, 80));//设置位置
        //group->setStyleSheet("#group{border:2px solid red;}");

        button->setText(filename);
        button->setStyleSheet("text-align: left;font-size:16px;color: white");
        button->setObjectName("button" + QString::number(m_iLabNum)); //设置名称，用于多按钮定位
        button->setVisible(true);
        group->show();
        //button->adjustSize();//自适应

        connect(button, SIGNAL(clicked(bool)), this, SLOT(MultiButtonClicked()));
        //connect(button, SIGNAL(floated()), this, SLOT(MultiButtonClicked()));

       //标签大小+标签个数*间隔+初始y值 调整框大小
        if ((m_iLabNum * 135 + 20) > (ui->scrollAreaWidgetContents_1->height() - 10))
        {
            int width = ui->scrollAreaWidgetContents_1->width();
            int height = ui->scrollAreaWidgetContents_1->height();
            ui->scrollAreaWidgetContents_1->setMinimumSize(width, height + 135);

        }
        m_iLabNum++;//类的成员数据，所以一直存在

    }

}

//浏览历史部分
void Medialibrary::BrowingHistorydisplay()
{
    //更新按钮，需要先删除之前的按钮
    h_iLabNum=0;
    qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<QGroupBox*>());
    qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<QLabel*>());
    qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<QPushButton*>());
    //生成按钮
    for (int i = file.historyNamelist.size()-1; i>=0 && h_iLabNum<=20; i--)
    {
        QString str=file.historyNamelist[i].c_str();
        QStringList strlist = str.split(".");//QString字符串分割函数
        QString name=QString("%1：").arg(h_iLabNum);
        QString filename = QString("%1").arg(strlist[0]);
        for (int i = 1; i < filename.length()/25+1; i++)
        {
                filename.insert(25*i, QString("\n"));
        }
          // str = "Hello World!"

        QGroupBox* group= new QGroupBox(ui->scrollAreaWidgetContents_2);//创建组
        QLabel* label = new QLabel;
        QLabel* image = new QLabel;
        
        QString image_Path = QString(":/icon/image%1.jpg").arg(media_image % 5);//待接口导入
        media_image++;
        QImage img = QImage(image_Path);
        image->setPixmap(QPixmap::fromImage(img));
        image->setScaledContents(true);
        image->setFixedSize(108, 63);

        label->setText(QString("%1").arg(strlist[1]));
        label->setStyleSheet("text-align: right;font-size:15px;color:gray");

        QPushButton* button = new QPushButton(ui->scrollAreaWidgetContents_2);//创建按钮
        QGridLayout* GLayout_0 = new QGridLayout;
        GLayout_0->addWidget(image, 0,0,2,1);
        GLayout_0->addWidget(button,0,1);
        GLayout_0->addWidget(label, 1,1);
        group->setLayout(GLayout_0);
        group->setGeometry(QRect(30,h_iLabNum * 120, 340, 80));//设置位置
        
        button->setText(filename);
        button->setStyleSheet("text-align: left;font-size:16px;color: white");
        button->setObjectName("historybutton" + QString::number(h_iLabNum)); //设置名称，用于多按钮定位
        button->setVisible(true);
        group->show();
        //button->adjustSize();//自适应
        
        if (file.historyExistlist[i]==0)
        {
            qDebug()<<"shide";
            QPalette   pal;
            pal.setColor(QPalette::ButtonText, QColor(255,0,0));
            button->setPalette(pal);
        }
        

        connect(button,SIGNAL(clicked(bool)),this,SLOT(MultiButtonClicked()));//绑定按钮按下和

       //标签大小+标签个数*间隔+初始y值 调整框大小
        if((h_iLabNum*135+20)>(ui->scrollAreaWidgetContents_2->height()-10))
        {
            int width=ui->scrollAreaWidgetContents_2->width();
            int height=ui->scrollAreaWidgetContents_2->height();
            ui->scrollAreaWidgetContents_2->setMinimumSize(width,height+135);
            //qDebug()<<ui->scrollAreaWidgetContents_2->height();

        }
        h_iLabNum++;//类的成员数据，所以一直存在

    }

    

}

//点击按钮获得文件名
void Medialibrary::MultiButtonClicked()
{
    QString btnName = QObject::sender()->objectName();
    qDebug() << btnName;
    //点击的文件名ID
    int index;
    string choosefile;
    if (btnName.mid(0,1)=='b')
    {
        index = (btnName.mid(6,-1)).toInt();//点击媒体库 
        choosefile=file.filePathlist[index].c_str();
    }
    else
    {
        index = (btnName.mid(13,-1)).toInt();//点击浏览记录 
        choosefile=file.historyPathlist[file.historyNamelist.size()-1-index].c_str();
    }

    file.saveChoosefile(choosefile);//存放完整路径到浏览记录

    QString file_path = choosefile.c_str();
    emit signal_mediafile_clicked(file_path);
    qDebug() << file_path;
       
    BrowingHistorydisplay();//更新浏览记录页面

}


//切换浏览记录和本地文件夹页
void Medialibrary::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());//得到按下的按钮的指针
    if(button==ui->mediaButton)
        ui->stackedWidget->setCurrentIndex(0);//根据按下的button按索引显示相应的页面
    else if(button==ui->browingButton)
        ui->stackedWidget->setCurrentIndex(1);
}


//导入文件夹按钮
void Medialibrary:: slot_media_floder_input()
{
    QString filepath=file.openExplorer(this).toUtf8();
    QString filePath = QDir::toNativeSeparators(filepath);//转为反斜杠
    file.dirPath = filePath;
    file.loadData();
    mediaListdisplay();
}

//全屏下隐藏媒体库
void Medialibrary::slot_medialibrary_resize(int width, int height)
{
    this->mainwindow_width = width;
    this->mainwindow_height = height;
    if (width < 1100)//是否全屏
    {
        this->setGeometry(670, 0, 350, height - this->console_height);
        this->show();
    }
    else
    {
        this->hide();
    }
}
//设置媒体库背景为透明s
void Medialibrary::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(192, 253, 123, 0));

}
