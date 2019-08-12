#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QtGui>
#include <QTimer>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(1080,720);

    //设置窗口名称
    this->setWindowTitle("地牢探险 MatchHack");

    //设置图标icon
    this->setWindowIcon(QIcon(":/pic/icon.png"));

    //设置鼠标样式
    QCursor cursor ;
    QPixmap pixmap(":/pic/mouse.png");
    pixmap = pixmap.scaled(pixmap.width()*0.2,pixmap.height()*0.2);
    cursor = QCursor(pixmap,0,1);
    setCursor(cursor) ;

    //背景乐
    QSound * startSound = new QSound(":/pic/mainScene.wav");
    startSound->play();
    startSound->setLoops(-1);//循环播放

    ismusic = 1;

    //点击音效
    QSound * clickSound = new QSound(":/pic/click2-1.wav");

    //new game按钮
    MyPushButton * newgameBtn = new MyPushButton(":/pic/NewGame.png",":/pic/havorNG.png");
    newgameBtn->setParent(this);
    newgameBtn->move(this->width()*0.5 - newgameBtn->width()*0.5, this->height()*0.55);

    //about us按钮
    MyPushButton * abBtn = new MyPushButton(":/pic/aboutus.png",":/pic/aboutH.png");
    abBtn->setParent(this);
    abBtn->move(this->width()*0.5 - abBtn->width()*0.5 - 8,this->height()*0.65);

    //音乐开关(on)
    MyPushButton * musicBtn = new MyPushButton(":/pic/sound_on.png",":/pic/sound_on.png");
    musicBtn->setParent(this);
    musicBtn->move(this->width()*0.5 - musicBtn->width()*0.5 ,this->height()*0.76);

    //音乐开关(off)
    MyPushButton * musicoffBtn = new MyPushButton(":/pic/sound_onH.png",":/pic/sound_onH.png");
    musicoffBtn->setParent(this);
    musicoffBtn->move(this->width()*0.5 - musicoffBtn->width()*0.5 ,this->height()*0.76);

    musicoffBtn->hide();//默认音乐开

    //关音乐
    connect(musicBtn,&MyPushButton::clicked,[=](){
        ismusic = 0;
       // clickSound->play();
        startSound->stop();
        musicoffBtn->show();
        musicBtn->hide();
    });

    //开音乐
    connect(musicoffBtn,&MyPushButton::clicked,[=](){
       clickSound->play();
       startSound->play();
       musicoffBtn->hide();
       musicBtn->show();
       ismusic = 1;
    });

    //开发者信息
    QLabel * devLabel = new QLabel;
    QPixmap pix;
    pix.load(":/pic/developers.png");
    devLabel->setGeometry(QRect(0,250,pix.width(),pix.height()));
    devLabel->setParent(this);
    devLabel->setPixmap(pix);
    devLabel->hide();

    //创建about us的关闭按钮
    MyPushButton * closeBtn = new MyPushButton(":/pic/close.png",":/pic/closeH.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()*0.95 - closeBtn->width()*0.5,this->height()*0.05);
    closeBtn->hide();

    //显示about us界面
    connect(abBtn,&MyPushButton::clicked,[=](){
       if(ismusic==1) clickSound->play();
        devLabel->show();
        closeBtn->show();
    });

    //隐藏about us界面
    connect(closeBtn,&MyPushButton::clicked,[=](){
       if(ismusic==1) clickSound->play();
       devLabel->hide();
       closeBtn->hide();
    });

    connect(newgameBtn, &MyPushButton::clicked, [=](){
        //选择难度窗口
        chooselevel = new ChooseLevel(nullptr,ismusic);

        //延时跳转选择难度窗口
        if(ismusic==1)
          clickSound->play();
        QTimer::singleShot(300,this,[=](){
            chooselevel->show();//显示选择难度窗口
            this->hide();//隐藏自己
          });

        connect(chooselevel,&ChooseLevel::stopmusic,[=](){
            startSound->stop();
        });

        //newgame到chooselevel时 判断主界面音乐开/关
        connect(chooselevel,&ChooseLevel::musicmw,[=](){
               if(ismusic) {
               startSound->play();
        }
        });

        //监听信号
        connect(chooselevel,&ChooseLevel::backPressed,[=](){
            //隐藏选择难度窗口 并显示主场景
            chooselevel->hide();
            this->show();
    //        startSound->stop();
        });
        });


}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //设置背景
    QPixmap pix;
    pix.load(":/pic/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题
    pix.load(":/pic/title.png");
    pix = pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,20,pix);

    //欢迎栏
    pix.load(":/pic/subtitle.png");
    pix = pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,160,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
