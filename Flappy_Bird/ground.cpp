#include "ground.h"
#include "birditem.h"
#include <QPixmap>
#include <QTimer>
#include <QPropertyAnimation>

groundItem::groundItem(QObject *parent) : QObject(parent) ,QGraphicsPixmapItem(QPixmap(":/ground.png"))
{
    //QGraphicsPixmapItem(QPixmap(":/ground.png"));
    setPos(0, 500);
    //生成地面向左移动的动画
    groundani = new QPropertyAnimation(this, "groundx", this);
    groundani->setStartValue(0);
    groundani->setEndValue(-100);
    groundani->setDuration(1000);
    groundani->setLoopCount(-1);   //一直循环
    groundani->start();

}
groundItem::groundItem(QString s,QObject *parent):QObject(parent),QGraphicsPixmapItem (QPixmap(s)),wingdirect(0),wingpos(0)
{
    setPos(0, 280);
    //生成地面向左移动的动画
    groundani = new QPropertyAnimation(this, "groundx", this);
    groundani->setStartValue(0);
    groundani->setEndValue(400);
    groundani->setDuration(2500);
    groundani->setLoopCount(-1);   //一直循环
    groundani->start();
    QTimer* wingtimer = new QTimer(this);
    connect(wingtimer,&QTimer::timeout,[=](){wings();});
    wingtimer->start(300);   //设置煽动翅膀时间（0.1s一次）
}
qreal groundItem::groundx() const
{
    return m_groundx;
}

void groundItem::setgroundx(qreal groundx)
{
    m_groundx = groundx;
    setPos(groundx, y());
}
void groundItem::groundstop()
{
    groundani->stop();
}
void groundItem::wings()
{
    if(wingpos==0)
    {
        setPixmap(QPixmap(":/1.png"));
        wingpos=1;
        wingdirect=0;
    }
    if(wingpos==1)
    {
        if(wingdirect==0)
        {
            setPixmap(QPixmap(":/2.png"));
            wingpos=2;
        }
        else
        {
            setPixmap(QPixmap(":/0.png"));
            wingpos=0;
        }
    }
    if(wingpos==2)
    {
        setPixmap(QPixmap(":/1.png"));
        wingpos=1;
        wingdirect=1;
    }
}
