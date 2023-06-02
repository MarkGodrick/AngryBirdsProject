#include "birditem.h"
#include "ground.h"
#include <QTimer>
#include <QGraphicsScene>

birditem::birditem(QPixmap pixmap, QObject *parent) : QObject(parent),
  wingdirect(0),wingpos(0),m_y(0)
{
    setPixmap(pixmap);

    //设置定时器 让鸟翅膀扇动
    QTimer* wingtimer = new QTimer(this);
    connect(wingtimer,&QTimer::timeout,[=](){wings();});
    wingtimer->start(100);   //设置煽动翅膀时间（0.1s一次）

    //计算地面位置
    groundline= scenePos().y()+450;

    //设置鸟的坠落
    goingdown = new QPropertyAnimation(this,"y",this);
    goingdown->setStartValue(scenePos().y());
    goingdown->setEndValue(groundline);
    goingdown->setEasingCurve(QEasingCurve::InQuad);
    goingdown->setDuration(1000);

    //设置坠落时的体态——嘴朝地
    rotating = new QPropertyAnimation(this,"rotation",this);
    rotating->setStartValue(rotation());
    rotating->setEndValue(90);
    rotating->setEasingCurve(QEasingCurve::InQuad);
    rotating->setDuration(1200);
}

//扇动翅膀函数
void birditem::wings()
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


qreal birditem::y() const
{
    return m_y;
}

qreal birditem::rotation() const
{
    return m_rotation;
}

void birditem::jump()
{
    goingdown->stop();
    rotating->stop();

    //让鸟跳跃完成后自然下坠
    connect(goingdown,&QPropertyAnimation::finished,[=]{falling();});

    //设置鸟的跳跃动画
    goingdown->setStartValue(y());
    goingdown->setEndValue(y() - 75);
    goingdown->setEasingCurve(QEasingCurve::OutQuad);
    goingdown->setDuration(255);
    goingdown->start();
    //设置鸟的跳跃旋转动画
    rotating->setStartValue(rotation());
    rotating->setEndValue(-20);
    rotating->setEasingCurve(QEasingCurve::InOutQuad);
    rotating->setDuration(200);
    rotating->start();
}

void birditem::birdstart()
{
    goingdown->start();
    rotating->start();
}

void birditem::birdstop()
{
    goingdown->stop();
    rotating->stop();
}

//碰撞检测函数
bool birditem::collision()
{
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
      foreach (QGraphicsItem * item , collidingItems)
      {
          groundItem * groundtemp = dynamic_cast<groundItem*>(item);
          if(groundtemp)
          {
              return true;
          }
      }
      return false;

}

void birditem::sety(qreal y)
{
    setPos(this->pos().x(),y);
    //若碰撞地板 则发出碰撞信号
    if(collision())
    {
        qDebug("collide!");
        emit collidesignal2();
    }

    m_y = y;
}

//将旋转中心放置鸟图元中心
void birditem::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF temp = boundingRect().center();
    setTransformOriginPoint(temp);
    QGraphicsItem::setRotation(rotation);
}

//鸟的自然下坠
void birditem::falling()
{
    if(y() < groundline)
    {
        rotating->stop();
        goingdown->setStartValue(y());
        goingdown->setEndValue(groundline);
        goingdown->setEasingCurve(QEasingCurve::InQuad);
        goingdown->setDuration(1000);
        goingdown->start();

        rotating->setStartValue(rotation());
        rotating->setEndValue(90);
        rotating->setEasingCurve(QEasingCurve::InQuad);
        rotating->setDuration(1000);
        rotating->start();
    }
}
