#ifndef HARD_H
#define HARD_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "cards.h"
#include "menu.h"
#include <QSound>
#include "lose.h"
#include "winfinal.h"

class hard : public QMainWindow
{
    Q_OBJECT
public:
    explicit hard(QWidget *parent = nullptr,bool ismusic = 0);
    int health=80;
    int level=1;
    int monhealth=80;

    //重写绘图事件
    void paintEvent(QPaintEvent *e);

    void reset();

    void exchangecards(Cards *card1,Cards *card2);

    void Flip(int i,int j,QSound * qsound);

    //宝箱效果
    void changeallcards();

       //卡牌正反的二维数组初始化，0代表正面，1代表背面
       int gameArray[4][4]={{0,0,0,0},
                            {0,0,0,0},
                            {0,0,0,0},
                            {0,0,0,0}};
       //卡牌类型的二维数组初始化
       int kindArray[4][4]={{1,1,2,2},
                            {3,3,4,4},
                            {6,6,7,7},
                            {8,8,9,9}};
       Cards *cardsArray[4][4];//金币数据
       int count=0;//记录每次翻转的操作步数
       int k;//用于保存当前位置
       int l;//用于保存当前位置
       int victoryflag=0;//匹配成功对数

       //menu
       menu * menuScene;

       //创建下一关窗口
       hard * hardScene;

       //lose window
       lose * loseScene;

       //win window
       winfinal * winfinalScene;

       Cards * tcard;

signals:
       void ng4();

public slots:
};

#endif // HARD_H
