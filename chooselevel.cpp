#include "chooselevel.h"
#include <QPainter>
#include <QTimer>
#include <iostream>

using namespace std;

ChooseLevel::ChooseLevel(QWidget *parent, bool ismusic1) : QMainWindow(parent)
{
    bool ismusic = ismusic1;

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

    //点击音效
    QSound * clickSound = new QSound(":/pic/click2-1.wav");

    //easy按钮
    MyPushButton * easyBtn = new MyPushButton(":/pic/easy.png",":/pic/easyH.png");
    easyBtn->setParent(this);
    easyBtn->move(this->width()*0.5 - easyBtn->width()*0.5, this->height()*0.58);

    connect(easyBtn,&MyPushButton::clicked,[=](){
            cout<<ismusic<<endl;
            if(ismusic==1) clickSound->play();
            emit this->stopmusic();
            this->hide();
            easyScene = new easy(nullptr,ismusic);
            easyScene->show();
            connect(easyScene,&easy::ng2,[=](){
                this->show();
                emit this->musicmw();//保持返回选难度界面后音乐开关与之前一致
            });
        });

    //medium按钮
    MyPushButton * mediumBtn = new MyPushButton(":/pic/Medium.png",":/pic/MediumH.png");
    mediumBtn->setParent(this);
    mediumBtn->move(this->width()*0.5 - mediumBtn->width()*0.5, this->height()*0.69);

    connect(mediumBtn,&MyPushButton::clicked,[=](){
            if(ismusic==1) clickSound->play();
            emit this->stopmusic();
            this->hide();
            mediumScene = new medium(nullptr,ismusic);
            mediumScene->show();
            connect(mediumScene,&medium::ng3,[=](){
                this->show();
                emit this->musicmw();
            });
        });

    //hard按钮
    MyPushButton * hardBtn = new MyPushButton(":/pic/hard.png",":/pic/hardH.png");
    hardBtn->setParent(this);
    hardBtn->move(this->width()*0.5 - hardBtn->width()*0.5, this->height()*0.81);

    connect(hardBtn,&MyPushButton::clicked,[=](){
           if(ismusic==1) clickSound->play();
           emit this->stopmusic();
           this->hide();
           hardScene = new hard(nullptr,ismusic);
           hardScene->show();
           connect(hardScene,&hard::ng4,[=](){
               this->show();
               emit this->musicmw();
           });
       });

    //exit按钮
    MyPushButton * exitBtn = new MyPushButton(":/pic/exit.png",":/pic/exitH.png");
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.88 - exitBtn->width()*0.5, this->height()*0.09);

    //实现返回功能
    connect(exitBtn,&MyPushButton::clicked,[=](){
       //发送返回信号
       if(ismusic==1) clickSound->play();
       emit this->backPressed();
    });
}


void ChooseLevel::paintEvent(QPaintEvent *)
{
    //设置背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题图
    pix.load(":/pic/title.png");
    pix = pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,20,pix);

    //设置副标题
    pix.load(":/pic/selectlevel.png");
    pix = pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,280,pix);

    //装饰
    pix.load(":/pic/gamer1.png");
    painter.drawPixmap(this->width()*0.15,400,pix);

}
