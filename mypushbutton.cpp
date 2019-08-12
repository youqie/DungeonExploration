#include "mypushbutton.h"

MyPushButton::MyPushButton( QString _normalImgPath, QString _pressedImgPath )
 {
    //保存选中前和选中后的图标路径
    this->normalImgPath = _normalImgPath;
    this->pressdImgPath = _pressedImgPath;

    setMouseTracking(true);

    pressdImg.load( this->pressdImgPath );
    bool ret = normalImg.load( this->normalImgPath );
    if(!ret)
    {
        QString str = QString("%1 图片加载失败").arg(this->normalImgPath);
        qDebug () << str;
        return;
    }

    //设定button大小
    this->setFixedSize(normalImg.width()*0.6,normalImg.height()*0.6);

    //设置不规则图片样式
    this->setStyleSheet( "QPushButton{border:0px;};" );

    //设置button
    this->setIcon(normalImg);

    //设置图片大小
    this->setIconSize(QSize(normalImg.width()*0.6,normalImg.height()*0.6));

}

//鼠标悬停效果
void MyPushButton::enterEvent(QEvent *event)
{
    this->setIcon(pressdImg);
}

//鼠标移出效果
void MyPushButton::leaveEvent(QEvent *event)
{
    this->setIcon(normalImg);
}
