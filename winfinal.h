#ifndef WINFINAL_H
#define WINFINAL_H

#include <QMainWindow>
#include "mypushbutton.h"
#include <QApplication>

class winfinal : public QMainWindow
{
    Q_OBJECT
public:
    explicit winfinal(QWidget *parent = nullptr,bool ismusic = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *e);

signals:
    void ngwin();//返回信号

public slots:
};

#endif // WINFINAL_H
