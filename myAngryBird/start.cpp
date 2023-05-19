#pragma execution_character_set("utf-8")
#include "start.h"
#include <QPainter>
#include <QMouseEvent>

Start::Start(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1800,967);
    setGeometry(750, 420,1800,967);
    this->setWindowIcon(QIcon(":/img/icon.png"));
    this->setWindowTitle("主菜单");
    //界面跳转
    choose = new chooselevel;
    connect(this, &Start::start, this, [&](){
        choose->setGeometry(this->geometry());
                choose->show();
    });//绑定当前界面 发射的start开始游戏的信号 给选择关卡界面choose 让它显示
    connect(choose, &chooselevel::choosesceneback, this, [&](){
        this->setGeometry(choose->geometry());
                this->show();
    });//绑定choose选择关卡界面 发射的choosesceneback返回信号 给当前界面 让它显示
    /*connect(choose, &choosepoint::choosesceneback, [=](){//绑定choose选择关卡界面 发射的choosesceneback返回信号 给当前界面 让它显示
        choose->hide();
        this->show();
    });*/
}
void Start::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, 1800, 967, QPixmap(":/img/start.jpg"));
    p.drawPixmap(1713, 10, 77, 32, QPixmap(":/img/BackButton.png"));
}
void Start::mousePressEvent(QMouseEvent *event)
{
    //点击密码的显示与隐藏
    if(event->pos().x() > 760 && event->pos().x() < 1040 && event->pos().y() > 510 && event->pos().y() < 640)
    {
        emit start();
        hide();//隐藏当前界面
    }
    if(event->pos().x() > 1713 && event->pos().x() < 1790 && event->pos().y() > 10 && event->pos().y() < 42)
    {
        emit back();
        hide();//隐藏当前界面
    }
}
