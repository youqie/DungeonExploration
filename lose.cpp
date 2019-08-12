#include "lose.h"
#include <QPainter>
#include <QSound>
#include <QTimer>

lose::lose(QWidget *parent,bool ismusic) : QMainWindow(parent)
{
    //点击音效
    QSound * clickSound = new QSound(":/pic/click2-1.wav");

    //设置固定大小
    this->setFixedSize(1080,800);

    //隐藏边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //设置透明度
    setAttribute(Qt::WA_TranslucentBackground);

    //设置鼠标样式
    QCursor cursor ;
    QPixmap pixmap(":/pic/mouse.png");
    pixmap = pixmap.scaled(pixmap.width()*0.2,pixmap.height()*0.2);
    cursor = QCursor(pixmap,0,1);
    setCursor(cursor) ;

    //新游戏
    MyPushButton * ngBtn = new MyPushButton(":/pic/menu_ng.png",":/pic/menu_ngH.png");
    ngBtn->setParent(this);
    ngBtn->move(this->width()*0.5-ngBtn->width()*0.5-5,this->height()*0.45);

    connect(ngBtn,&MyPushButton::clicked,[=](){
         if(ismusic) clickSound->play();
         this->close();
         emit ng();
     });

    //exit
    MyPushButton * exitBtn = new MyPushButton(":/pic/menu_ex.png",":/pic/menu_exH.png");\
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.5-exitBtn->width()*0.5-5,this->height()*0.56);

    //程序退出
    connect(exitBtn,&MyPushButton::clicked,[=](){
        if(ismusic==1) clickSound->play();
        QTimer::singleShot(430,this,[=](){
            QApplication::exit();
        });
    });
}
void lose::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //设置背景
    QPixmap pix;
    pix.load(":/pic/lose.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
