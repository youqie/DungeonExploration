#include "easy.h"
#include <QPainter>
#include <QSound>
#include <QTime>
#include <iostream>

using namespace std;
int ismusic1;

//点击音效
QSound * clickSound = new QSound(":/pic/click2-1.wav");

easy::easy(QWidget *parent,bool ismusic) : QMainWindow(parent)
{

    ismusic1=ismusic;

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

    //背景乐
    QSound * gameSound = new QSound(":/pic/gameScene.wav");
    if(ismusic==1) {gameSound->play();
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
    else mscBtn->hide();//随主界面音乐开关

    //关音乐
    connect(mscBtn,&MyPushButton::clicked,[=](){
       //clickSound->play();
       mscoffBtn->show();
       mscBtn->hide();
       gameSound->stop();
       ismusic1=0;
    });

    //开音乐
    connect(mscoffBtn,&MyPushButton::clicked,[=](){
       clickSound->play();
       mscoffBtn->hide();
       mscBtn->show();
       gameSound->play();
       gameSound->setLoops(-1);//循环播放
       ismusic1=1;
    });

    //链接窗口
    connect(menuBtn,&MyPushButton::clicked,[=](){
        if(ismusic1==1) clickSound->play();
        menuScene = new menu(nullptr,ismusic1);
        menuScene->show();
        connect(menuScene,&menu::ng,[=](){
            emit ng2();
            gameSound->stop();
            this->close();
        });
    });

    //随机生成卡牌分布，通过随机交换既定好的位置实现随机分布
          qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
          for(int i=0;i<3;i++)
          {
              for(int j=0;j<3;j++)
              {
                  int a = qrand()%3;   //随机生成0到3的随机数
                  int b = qrand()%3;   //随机生成0到3的随机数
                  if((i==1&&j==1)||(a==1&&b==1)){}
                  else{
                      int t = kindArray[i][j];   //交换kindArray[i][j]与kindArray[a][b]
                      kindArray[i][j]=kindArray[a][b];
                      kindArray[a][b]=t;}

              }
          }

          //创建游戏主场景
          for(int i = 0 ; i < 3 ;i ++)
              for(int j = 0 ; j < 3 ; j++)
              {
                  if(i==1&&j==1) {} else Flip(i,j,gameSound);
              }
}

void easy::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //设置背景
    QPixmap pix;
    pix.load(":/pic/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //玩家信息
    pix.load(":/pic/vs.png");
    painter.drawPixmap(600,310,pix);

    //显示logo
    pix.load(":/pic/gametitle.png");
    pix = pix.scaled(pix.width()*1.2,pix.height()*1.2);
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,this->height()*0.05-10,pix);

    //显示血条边框
    pix.load(":/pic/lifebar-red.png");
    pix = pix.scaled((pix.width()-6)*1.1,pix.height()*1.1);
    painter.drawPixmap(755,395,pix);

    //显示血条
    pix.load(":/pic/lifebar.png");
    pix = pix.scaled(health*2*1.1,pix.height()*1.1);
    painter.drawPixmap(755,395,pix);

    //显示monster血条边框
    pix.load(":/pic/lifebar-red.png");
    pix = pix.scaled((pix.width()-6)*1.1,pix.height()*1.1);
    painter.drawPixmap(755,595,pix);

    //显示monster血条
    pix.load(":/pic/lifebar.png");
    pix = pix.scaled(monhealth*2*1.1,pix.height()*1.1);
    painter.drawPixmap(755,595,pix);

    //显示第几关
    switch(level)
    {
        case 1:
        pix.load(":/pic/level1.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(655,210,pix);break;
        case 2:
        pix.load(":/pic/level2.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(655,210,pix);break;
        case 3:
        pix.load(":/pic/level3.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(655,210,pix);break;
        case 4:
        pix.load(":/pic/level4.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(655,210,pix);break;
        case 5:
        pix.load(":/pic/level5.png");
        pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
        painter.drawPixmap(655,210,pix);break;
    }
}


//实现金币的创建和翻转
void easy::Flip(int i,int j,QSound * qsound)
{
    Cards * cards = new Cards(":/pic/box1.png");
    cards->posX = i ;//记录x位置
    cards->posY = j ;//记录y位置
    cards->flag = gameArray[i][j];//记录正反面
    cards->kind = kindArray[i][j];//记录类型
    cards->setParent(this);
    cards->move(100+i*135,220+j*135);

    //将cards数据放入维护的二维数组中
    cardsArray[i][j]=cards;


    connect(cards,&Cards::clicked,[=](){
        if(ismusic1==1) clickSound->play();
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
                health-=10;
                this->update();//更新窗口
                cardsArray[i][j]->changeFlag();
                gameArray[i][j] = gameArray[i][j]== 0 ? 1 : 0;
                cardsArray[k][l]->changeFlag();
                gameArray[k][l] = gameArray[k][l]== 0 ? 1 : 0;
            }
            else
            {
                if(kindArray[i][j]==5)
                {
                    if(health<=60)
                    {
                        health+=20;//如果血量在60以下
                    }
                    else {
                        health=80;//如果血量在60以上，则血量升至80
                    }
                    this->update();//更新窗口
                }
                victoryflag++;//匹配成功对数加一
                monhealth-=20;
                this->update();//更新窗口
            }
            // 重置步数
            count=0;
            //如果已经成功匹配了4对，则游戏胜利
            if(victoryflag==4)
            {
                if(level==5)//如果当前关卡为最后一关
                {                                  
                    winfinalScene = new winfinal(nullptr,ismusic1);
                    winfinalScene->show();
                    connect(winfinalScene,&winfinal::ngwin,[=](){
                    emit ng2();
                    qsound->stop();
                    this->close();
                    });
                }
                else{
                    this->reset();
                }
            }
            else if(health==0)
            {
                loseScene = new lose(nullptr,ismusic1);
                loseScene->show();
                connect(loseScene,&lose::ng,[=](){
                emit ng2();
                qsound->stop();
                this->close();
               });
            }
        }
    }
    });
}

void easy::reset(){
    for(int z=0;z<3;z++)
    {
        for(int b=0;b<3;b++)
        {
            if(!(z==1&&b==1)){
            if(gameArray[z][b]==1){
                cardsArray[z][b]->changeFlag();//将所有背面牌翻至正面
                gameArray[z][b] = 0;
            }}
        }
    }
    monhealth=80;//更新怪物生命值
    level+=1;//关卡+1
    //随机生成卡牌分布，通过随机交换既定好的位置实现随机分布
       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               int a = qrand()%3;   //随机生成0到3的随机数
               int b = qrand()%3;   //随机生成0到3的随机数
               if((i==1&&j==1)||(a==1&&b==1))
               {
                   ;
               }
               else{
               int t = kindArray[i][j];   //交换kindArray[i][j]与kindArray[a][b]
               kindArray[i][j]=kindArray[a][b];
               kindArray[a][b]=t;
               exchangecards(cardsArray[i][j],cardsArray[a][b]);//交换cardsArray
               }
           }
       }

    this->update();
    victoryflag=0;//重置判断胜利的标志
    cout << level << endl;
}

void easy::exchangecards(Cards *card1,Cards *card2)
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
