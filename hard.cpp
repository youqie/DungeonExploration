#include "hard.h"
#include <QPainter>
#include <QTime>
#include <QEventLoop>
#include <QLabel>
#include <iostream>
#include<QPixmap>
#include <QSound>

using namespace std;
bool ismusic2;

hard::hard(QWidget *parent,bool ismusic) : QMainWindow(parent)
{
    ismusic2=ismusic;

    this->update();//更新组件
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

    //菜单按钮
    MyPushButton * menuBtn = new MyPushButton(":/pic/menu.png",":/pic/menuH.png");
    menuBtn->setParent(this);
    menuBtn->move(this->width()*0.065 - menuBtn->width()*0.5, this->height()*0.05);

    //点击音效
    QSound * clickSound = new QSound(":/pic/click2-1.wav");

    //背景乐
    QSound * gameSound = new QSound(":/pic/gameScene.wav");
    if(ismusic) {gameSound->play();
    gameSound->setLoops(-1);}//循环播放

    //音乐开关按钮(state on)
    MyPushButton * mscBtn = new MyPushButton(":/pic/musicBtn.png",":/pic/musicBtnH.png");
    mscBtn->setParent(this);
    mscBtn->move(this->width()*0.145 - mscBtn->width()*0.5, this->height()*0.05);

    //音乐开关按钮(state off)
    MyPushButton * mscoffBtn = new MyPushButton(":/pic/musicOff.png",":/pic/musicOffH.png");
    mscoffBtn->setParent(this);
    mscoffBtn->move(this->width()*0.145 - mscBtn->width()*0.5, this->height()*0.05);

    if(ismusic==1)
        mscoffBtn->hide();
    else mscBtn->hide();

    //关音乐
    connect(mscBtn,&MyPushButton::clicked,[=](){
       mscoffBtn->show();
       mscBtn->hide();
       gameSound->stop();
       ismusic2=0;
    });

    //开音乐
    connect(mscoffBtn,&MyPushButton::clicked,[=](){
       clickSound->play();
       mscoffBtn->hide();
       mscBtn->show();
       gameSound->play();
       ismusic2=1;
    });

    //链接窗口
    connect(menuBtn,&MyPushButton::clicked,[=](){
        if(ismusic2) clickSound->play();
        menuScene = new menu(nullptr,ismusic2);
        menuScene->show();
        connect(menuScene,&menu::ng,[=](){
            emit ng4();
            gameSound->stop();
            this->close();
        });
    });

    //随机生成卡牌分布，通过随机交换既定好的位置实现随机分布
       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
       for(int i=0;i<4;i++)
       {
           for(int j=0;j<4;j++)
           {
               int a = qrand()%3;   //随机生成0到3的随机数
               int b = qrand()%3;   //随机生成0到3的随机数
               int t = kindArray[i][j];   //交换kindArray[i][j]与kindArray[a][b]
               kindArray[i][j]=kindArray[a][b];
               kindArray[a][b]=t;
           }
       }

       //创建游戏主场景
       for(int i = 0 ; i < 4 ;i ++)
           for(int j = 0 ; j < 4 ; j++)
               Flip(i,j,gameSound);
}

void hard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //设置背景
    QPixmap pix;
    pix.load(":/pic/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //显示logo
    pix.load(":/pic/gametitle.png");
    pix = pix.scaled(pix.width()*1.2,pix.height()*1.2);
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,this->height()*0.05-10,pix);

    //玩家信息
    pix.load(":/pic/vs.png");
    painter.drawPixmap(670,280,pix);

    //显示血条边框
    pix.load(":/pic/lifebar-red.png");
    pix = pix.scaled((pix.width()-6)*1.1,pix.height()*1.1);
    painter.drawPixmap(825,365,pix);

    //显示血条
    pix.load(":/pic/lifebar.png");
    pix = pix.scaled(health*2*1.1,pix.height()*1.1);
    painter.drawPixmap(825,365,pix);

    //显示monster血条边框
    pix.load(":/pic/lifebar-red.png");
    pix = pix.scaled((pix.width()-6)*1.1,pix.height()*1.1);
    painter.drawPixmap(825,565,pix);

    //显示monster血条
    pix.load(":/pic/lifebar.png");
    pix = pix.scaled(monhealth*2*1.1,pix.height()*1.1);
    painter.drawPixmap(825,565,pix);

    //显示第几关
    switch(level)
    {
        case 1:
        pix.load(":/pic/level1.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(725,190,pix);break;
        case 2:
        pix.load(":/pic/level2.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(725,190,pix);break;
        case 3:
        pix.load(":/pic/level3.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(725,190,pix);break;
        case 4:
        pix.load(":/pic/level4.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(725,190,pix);break;
        case 5:
        pix.load(":/pic/level5.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(725,190,pix);break;
    }
}

void hard::changeallcards(){
    for(int t=0;t<4;t++)
    {
        for(int m=0;m<4;m++)
        {
            if(gameArray[t][m]==0){
                cardsArray[t][m]->changeFlag();//将所有正面牌翻转至背面
            }
        }
    }
    //给玩家2s的记忆时间
    QEventLoop eventloop;
    QTimer::singleShot(2000, &eventloop, SLOT(quit()));
    eventloop.exec();
    for(int q=0;q<4;q++)
    {
        for(int w=0;w<4;w++)
        {
            if(gameArray[q][w]==0){
                cardsArray[q][w]->changeFlag();//将所有背面牌翻转至正面
            }
        }
    }
}

//实现金币的创建和翻转
void hard::Flip(int i,int j,QSound * gameSound)
{
    Cards * cards = new Cards(":/pic/box1.png");
    cards->posX = i ;//记录x位置
    cards->posY = j ;//记录y位置
    cards->flag = gameArray[i][j];//记录正反面
    cards->kind = kindArray[i][j];//记录类型
    cards->setParent(this);
    cards->move(70+i*135,140+j*135);

    //将cards数据放入维护的二维数组中
    cardsArray[i][j]=cards;


    connect(cards,&Cards::clicked,[=](){
        //点击音效
        QSound * clickSound = new QSound(":/pic/click2-1.wav");
        if(ismusic2) clickSound->play();
        if(gameArray[i][j]==0)//如果卡牌已经翻开，则点击无法触发翻转
        {
        cards->changeFlag();
        gameArray[i][j] = gameArray[i][j]== 0 ? 1 : 0;
        count++;//计步
        if(count==1)//第一步
        {
            k=i;//保存当前翻开卡牌的x
            l=j;//保存当前翻开卡牌的y
        }
        else if(count==2)//第二步
        {
            //延迟翻转回去
            QEventLoop eventloop;
            QTimer::singleShot(300, &eventloop, SLOT(quit()));
            eventloop.exec();
            if(cardsArray[i][j]->kind!=cardsArray[k][l]->kind)
            {
                //如果第一步和第二步的类型不同则执行翻转
                health-=5;
                this->update();//更新窗口
                cardsArray[i][j]->changeFlag();
                gameArray[i][j] = gameArray[i][j]== 0 ? 1 : 0;
                cardsArray[k][l]->changeFlag();
                gameArray[k][l] = gameArray[k][l]== 0 ? 1 : 0;
            }
            else
            {
                if(kindArray[i][j]==1)
                {
                   changeallcards();
                }

                victoryflag++;//匹配成功对数加一
                monhealth-=10;
                this->update();
            }
            // 重置步数
            count=0;
            //如果已经成功匹配了8对，则游戏胜利
            if(victoryflag==8)
            {
                if(level==5)
                {
                    winfinalScene = new winfinal(nullptr,ismusic2);
                    winfinalScene->show();
                    connect(winfinalScene,&winfinal::ngwin,[=](){
                    emit ng4();
                    gameSound->stop();
                    this->close();
                    });
                }
                else {
                    this->reset();
                }
            }
            else if(health==0)
            {
                loseScene = new lose(nullptr,ismusic2);
                loseScene->show();
                connect(loseScene,&lose::ng,[=](){
                    emit ng4();
                    gameSound->stop();
                    this->close();
                });
            }
        }
    }
    });
}

void hard::reset(){
    for(int z=0;z<4;z++)
    {
        for(int b=0;b<4;b++)
        {
            if(gameArray[z][b]==1){
                cardsArray[z][b]->changeFlag();//将所有背面牌翻至正面
                gameArray[z][b] = 0;
            }
        }
    }
    monhealth=80;//更新怪物生命值
    level+=1;//关卡+1
    //随机生成卡牌分布，通过随机交换既定好的位置实现随机分布
       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
       for(int i=0;i<4;i++)
       {
           for(int j=0;j<4;j++)
           {
               int a = qrand()%3;   //随机生成0到3的随机数
               int b = qrand()%3;   //随机生成0到3的随机数
               int t = kindArray[i][j];   //交换kindArray[i][j]与kindArray[a][b]
               kindArray[i][j]=kindArray[a][b];
               kindArray[a][b]=t;
               exchangecards(cardsArray[i][j],cardsArray[a][b]);//交换cardsArray
           }
       }

    this->update();
    victoryflag=0;//重置判断胜利的标志
    cout << level << endl;
}
void hard::exchangecards(Cards *card1,Cards *card2)
{
    //交换两个cards对象
    tcard=new Cards(":/pic/box1.png");
    tcard->flag=card1->flag;
    tcard->kind=card1->kind;
    tcard->max=card1->max;
    tcard->min=card1->min;
    tcard->posX=card1->posX;
    tcard->posY=card1->posY;
    card1->flag=card2->flag;
    card1->kind=card2->kind;
    card1->max=card2->max;
    card1->min=card2->min;
    card1->posX=card2->posX;
    card1->posY=card2->posY;
    card2->flag=tcard->flag;
    card2->kind=tcard->kind;
    card2->max=tcard->max;
    card2->min=tcard->min;
    card2->posX=tcard->posX;
    card2->posY=tcard->posY;
}

