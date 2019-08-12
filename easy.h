#ifndef EASY_H
#define EASY_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "menu.h"
#include "cards.h"
#include <QSound>
#include "winfinal.h"
#include "lose.h"

class easy : public QMainWindow
{
    Q_OBJECT
public:
    explicit easy(QWidget *parent = nullptr,bool ismusic = 0);
    int health=80;//玩家血量
    int level=1;//关卡
    int monhealth=80;//monster血量

    //重写绘图事件
    void paintEvent(QPaintEvent *e);

    void Flip(int i,int j, QSound * qsound);


    void reset();

    void exchangecards(Cards *card1,Cards *card2);

           //卡牌正反的二维数组初始化，0代表正面，1代表背面
           int gameArray[3][3]={{0,0,0},
                                {0,1,0},
                                {0,0,0}};
           //卡牌类型的二维数组初始化
           int kindArray[3][3]={{3,3,2},
                                {2,3,4},
                                {4,5,5}};
           Cards *cardsArray[3][3];//金币数据
           int count=0;//记录每次翻转的操作步数
           int k;//用于保存当前位置
           int l;//用于保存当前位置
           int victoryflag=0;//匹配成功对数

    //创建menu窗口
    menu * menuScene;

    //创建下一关窗口
    easy * easyScene;

    //lose window
    lose * loseScene;

    //win window
    winfinal * winfinalScene;

    //用于交换对象
    Cards * tcard;

signals:
      void ng2();

public slots:
};

#endif // EASY_H
