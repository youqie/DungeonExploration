#ifndef MEDIUM_H
#define MEDIUM_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "cards.h"
#include "menu.h"
#include "winfinal.h"
#include <QSound>
#include "lose.h"

class medium : public QMainWindow
{
    Q_OBJECT
public:

    //重写绘图事件
    void paintEvent(QPaintEvent *e);

    explicit medium(QWidget *parent = nullptr,bool ismusic = 0);

    int health=80;
    int level=1;
    int monhealth=80;

    void reset();

    void exchangecards(Cards *card1,Cards *card2);

    void Flip(int i,int j,QSound * qsound);

    void changeallcards();


       //卡牌正反的二维数组初始化，0代表正面，1代表背面
       int gameArray[4][4]={{0,0,0,0},
                            {0,0,0,0},
                            {0,0,0,0},
                            {0,0,0,0}};
       //卡牌类型的二维数组初始化
       int kindArray[4][4]={{9,9,1,1},
                            {3,3,4,4},
                            {5,5,6,6},
                            {7,7,8,8}};
       Cards *cardsArray[4][4];//金币数据
       int count=0;//记录每次翻转的操作步数
       int k;//用于保存当前位置
       int l;//用于保存当前位置
       int victoryflag=0;//匹配成功对数

       //创建menu窗口
       menu * menuScene;

       //创建下一关窗口
       medium * mediumScene;

       //lose窗口
       lose * loseScene;

       //winfinal窗口
       winfinal * winfinalScene;

       Cards * tcard;
signals:
       void ng3();

public slots:
};

#endif // MEDIUM_H
