#include "cards.h"
#include<QPixmap>
#include<QMessageBox>
#include<QString>
Cards::Cards(QString CardImg)
{
    QPixmap pix;
    bool ret = pix.load(CardImg);
    if(!ret)
    {
        QString str=QString("图片加载失败 %1").arg(CardImg);
        QMessageBox::critical(this,"加载失败",str);
        return;
    }

    this->setFixedSize(pix.width()*0.9,pix.height()*0.9);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()*0.9,pix.height()*0.9));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听定时器
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        switch(this->kind){
            case 1:{QString str = QString(":/pic/box%1.png").arg(this->min++);
                    pix.load(str);break;}//宝箱的翻转动画
            case 2:{QString str = QString(":/pic/hammer%1.png").arg(this->min++);
                    pix.load(str);break;}//锤子的翻转动画
            case 3:{QString str = QString(":/pic/hook%1.png").arg(this->min++);
                    pix.load(str);break;}//钩子的翻转动画
            case 4:{QString str = QString(":/pic/knife%1.png").arg(this->min++);
                    pix.load(str);break;}//小刀的翻转动画
            case 5:{QString str = QString(":/pic/potion%1.png").arg(this->min++);
                    pix.load(str);break;}//药水的翻转动画
            case 6:{QString str = QString(":/pic/shield%1.png").arg(this->min++);
                    pix.load(str);break;}//盾牌的翻转动画
            case 7:{QString str = QString(":/pic/staff%1.png").arg(this->min++);
                    pix.load(str);break;}//法杖的翻转动画
            case 8:{QString str = QString(":/pic/star%1.png").arg(this->min++);
                    pix.load(str);break;}//星星法杖的翻转动画
            case 9:{QString str = QString(":/pic/sword%1.png").arg(this->min++);
                    pix.load(str);break;}//星星法杖的翻转动画
        }


        this->setFixedSize(pix.width()*0.9,pix.height()*0.9);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.9,pix.height()*0.9));


        //如果显示到了最后一张图片 停止计时器
        if(this->min>this->max)
        {
            this->min=1;
            timer1->stop();
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        switch(this->kind){
            case 1:{QString str = QString(":/pic/box%6.png").arg(this->max--);
            pix.load(str);break;}//宝箱的翻转动画
            case 2:{QString str = QString(":/pic/hammer%6.png").arg(this->max--);
            pix.load(str);break;}//锤子的翻转动画
            case 3:{QString str = QString(":/pic/hook%6.png").arg(this->max--);
            pix.load(str);break;}//钩子的翻转动画
            case 4:{QString str = QString(":/pic/knife%6.png").arg(this->max--);
            pix.load(str);break;}//小刀的翻转动画
            case 5:{QString str = QString(":/pic/potion%6.png").arg(this->max--);
            pix.load(str);break;}//药水的翻转动画
            case 6:{QString str = QString(":/pic/shield%6.png").arg(this->max--);
            pix.load(str);break;}//盾牌的翻转动画
            case 7:{QString str = QString(":/pic/staff%6.png").arg(this->max--);
            pix.load(str);break;}//法杖的翻转动画
            case 8:{QString str = QString(":/pic/star%6.png").arg(this->max--);
            pix.load(str);break;}//星星的翻转动画
            case 9:{QString str = QString(":/pic/sword%6.png").arg(this->max--);
            pix.load(str);break;}//星星的翻转动画

        }

        this->setFixedSize(pix.width()*0.9,pix.height()*0.9);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.9,pix.height()*0.9));
        //如果显示到了最后一张图片 停止计时器
        if(this->max<this->min)
        {
            this->max=6;
            timer2->stop();
        }
    });
}

void Cards::changeFlag()
{
    if(this->flag==0)
    {
        //开启正面翻反面的定时器
        timer1->start(30);
        //同步标志
        this->flag=true;
    }
    else
    {
        //开启反面翻正面的定时器
        timer2->start(30);
        //同步标志
        this->flag=false;
    }
}//改变状态，执行翻转效果
