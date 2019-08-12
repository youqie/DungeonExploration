#ifndef CARDS_H
#define CARDS_H

#include <QPushButton>
#include <QTimer>

class Cards : public QPushButton
{
    Q_OBJECT
public:
    //explicit Cards(QWidget *parent = nullptr);
    //参数 功能 显示默认是正面还是背面
    Cards(QString CardImg);

    int posX;  //x坐标
    int posY;  //y坐标
    bool flag;  //正反标志
    int kind;   //道具类型
                //1代表宝箱 2代表锤子 3代表钩子 4代表小刀 5代表药水 6代表盾牌 7代表法杖 8代表星星法杖 9代表剑
    void changeFlag();//改变状态，实现正反面翻转
    QTimer *timer1;//正面翻反面 定时器
    QTimer *timer2;//反面翻正面 定时器
    int min =1;//最小图片
    int max =6;//最大图片
signals:

public slots:
};

#endif // CARDS_H
