#include "shot.h"
#include <QMouseEvent>
#include <QPainter>
#include <QIcon>
#include <QMessageBox>
#include <qDebug>


slingshot::slingshot(int xx ,QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(1800, 967);
    setGeometry(70,50,1800,967);
    this->setWindowIcon(QIcon(":/img/yellow_bird.png"));
    this->setWindowTitle("愤怒的小鸟");
    check = new datacheck(xx, this);    //选择小鸟的关数
    connect(check->b, &bird::bird_move, this, &slingshot::slig);


    connect(this, &slingshot::Releaseline, this, [&](){
        check->b->timer->start(30);
    });

    connect(check->b->timer, &QTimer::timeout, [&](){
       check->b->port( vx, vy,  resistance_const, accg);
    });

}
void slingshot::paintEvent(QPaintEvent *event)
{
    //画弹弓支架
    QPainter p(this);
    p.drawPixmap(0, 0, 1800,967, QPixmap(":/img/bord.jpg"));
    p.drawPixmap(1740, 10, 50, 50, QPixmap(":/img/exit.png"));
    QPen pen; //画笔，画线用
    pen.setWidth(10);
    p.setPen(pen);//把笔给画家
    p.drawLine(QPoint(460,616), QPoint(440, 546));
    p.drawLine(QPoint(460,616), QPoint(490, 556));
    p.drawLine(QPoint(460,616), QPoint(460, 726));

    //画弹弓皮筋
    QPainter plin1(this);
    QPainter plin2(this);
    pen.setColor(Qt::red);
    plin1.setPen(pen);//把笔给画家
    plin2.setPen(pen);//把笔给画家
    plin1.drawLine(QPoint(440,546), posline);
    plin2.drawLine(posline, QPoint(490, 556));
    //画中心拉力点
    QPainter point(this);
    pen.setWidth(20);
    pen.setColor(Qt::black);
    point.setPen(pen);//把笔给画家
    point.drawPoint(posline);

    qDebug() << pullflag << "pullflag";

}
void slingshot::mouseMoveEvent(QMouseEvent *event)
{
//    //判断拉动皮筋
//    if(event->pos().x() > 440 && event->pos().x() < 490 && event->pos().y() > 546 && event->pos().y() < 556)
//        pullflag = true;
//    if(pullflag && event->pos().x() >0 && event->pos().x() < 900 && event->pos().y() > 0 && event->pos().y() < 967)
//        posline = event->pos();
//    update();
}
void slingshot::mouseReleaseEvent(QMouseEvent *event)
{
//    if(check->b->flag_move == false)
//        posline = QPoint(465, 551);
    check->b->flag_move = false;
    //判断在拉动皮筋后松开皮筋
    if(pullflag)
    {
        pullflag = false;
        emit Releaseline();

        check->b->current_vx = check->b->current_vy = 0;
        vx = 465 - posline.x();
        vy = 551 - posline.y();
        resistance_const = 0.0003;
        accg = 20.6;



    }
    update();
}
void slingshot::mousePressEvent(QMouseEvent *event)
{
    //退出游戏
    if(event->pos().x() > 1740 && event->pos().x() < 1790 && event->pos().y() > 10 && event->pos().y() < 60)
    {
          QMessageBox msgBox;
          msgBox.setWindowIcon(QIcon(":/img/red_bird.png"));
          msgBox.setIconPixmap(QPixmap(":/img/icon.png"));
          msgBox.setText("你确定要退出游戏吗?");
          msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
          if( QMessageBox::Yes == msgBox.exec())
          {
              emit back();
              hide();//隐藏当前界面
          }
    }
}

void slingshot::slig(QPoint p)
{
    //判断拉动皮筋
    if(p.x() > 440 && p.x() < 490 && p.y() > 546 && p.y() < 556)
        pullflag = true;
    if(pullflag == true)
    {
        if(pullflag && p.x() >100 && p.x() < 763 && p.y() > 240 && p.y() < 840)
            posline = p;
    }else {
        posline = QPoint(465, 551);
    }

    if(check->b->flag_move == false)
    {
        posline = QPoint(465, 551);
    }


    update();
}
