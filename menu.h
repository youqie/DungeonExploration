#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "mypushbutton.h"
#include <QApplication>

class menu : public QMainWindow
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = nullptr,bool ismusic = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

signals:
    void ng();//new game信号->easy/medium/hard

public slots:
};

#endif // MENU_H
