#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "easy.h"
#include "hard.h"
#include "medium.h"

class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr, bool ismusic = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //easy跳转
    easy * easyScene;

    //medium跳转
    medium * mediumScene;

    //hard跳转
    hard * hardScene;

signals:
    void backPressed();//点击exit后返回的信号
    void stopmusic();//停止音乐信号
    void musicmw();//向主窗口传输音乐开关信号

public slots:
};

#endif // CHOOSELEVEL_H
