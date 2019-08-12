#ifndef LOSE_H
#define LOSE_H

#include <QMainWindow>
#include "mypushbutton.h"
#include <QApplication>

class lose : public QMainWindow
{
    Q_OBJECT
public:
    explicit lose(QWidget *parent = nullptr,bool ismusic = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);
signals:
    void ng();//lose信号->easy/medium/hard

public slots:
};

#endif // LOSE_H
