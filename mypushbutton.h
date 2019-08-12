#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    MyPushButton( QString normalImg, QString pressImg = "" );

    QString normalImgPath;//默认显示图片路径
    QString pressdImgPath;//鼠标移入后显示图片路径

    QPixmap pressdImg;
    QPixmap normalImg;

    //鼠标移入移出事件
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);


signals:

public slots:
};



#endif // MYPUSHBUTTON_H
