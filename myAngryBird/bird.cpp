#include "bird.h"
#include <QPixmap>
#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QTimer>

bird::bird(QString normalImg)
{
    ImagPath = normalImg;
    pix = new QPixmap;
    bool ret = pix->load(normalImg);
    if(!ret){
        qDebug() << "图片加载失败";
        return;
    }
    *pix = pix->scaled(pix->width() * 0.08, pix->height() * 0.08);
    setFixedSize(pix->width() * 0.08, pix->height() * 0.08);
    setMask( pix->mask() );
    setMinimumHeight(pix->height());
    setMinimumWidth(pix->width());

    mid_width = pix->width() * 0.08;
    mid_height = pix->height() * 0.08;

    qDebug() << "brid " << "w " << mid_width << "h " << mid_height;

    mid_pos = new QPoint(pix->width() * 0.08 / 2, pix->height() * 0.08 / 2);
    //mid_pos = QPoint(pix->width() * 0.08 / 2, pix->height() * 0.08 / 2);

    time = 0;
    bird_weight = 3;
    vx_flag = true;
    flag_move = false;

    timer = new QTimer(this);
}

void bird::port(qreal vx, qreal vy, qreal resistance_const, qreal accg) //自己模拟的控器环境
{
    if(current_vy == 0 && current_vx == 0 && time == 0) //速度为和时间都为0时重新获取当前速度
    {

        current_vx = vx;
        current_vy = vy;
        if(vy > 0)
        {
            flag = true;
        }else {
            flag = false;
        }

        this->resistance_const = resistance_const;
        this->accg = accg;

    }

   if(time == 0) //时间为0时重置获取当前左上角位置
   {
        wpos = this->geometry().topLeft();
        track_x = track_y = 0;
   }

    resistance_ax = resistance_const * current_vx * current_vx / bird_weight;   //模拟空气阻力
    last_vx = current_vx;
    if(current_vx > 0)
    {
        current_vx -= (resistance_ax + 0.4 * 0.01);
    }else if(current_vx < 0)
    {
        current_vx += (resistance_ax + 0.4 * 0.01);
    }
    if(flag == true)    //y方向上的运动
    {
        current_vy +=  (accg * 0.1 - 0.9);
        energy -= (accg * 0.1 + 0.9);
        if(energy < 0)
            flag = false;
    }else
    {
        current_vy +=  (accg * 0.1 + 0.9);
        energy += (accg * 0.1);
        if(current_vy > 0)
            flag = true;
    }


    if( qAbs(current_vx + last_vx) != qAbs(qAbs(current_vx) + qAbs(last_vx)) ) //单位统一
    {
        vx_flag = false;
    }

    time += 0.1;


    qDebug() << current_vx << "vx";
    qDebug() << current_vy << "vy";
    if(vx_flag == true) //  x方向上的运动
    {
        track_x += current_vx * 0.1;

    }

        track_y += current_vy * 0.1;



    qDebug() << wpos.x() + track_x << wpos.y() + track_y;
    qDebug() << "time :" << time;

    if(time > 25.0) //超过25个时钟点重置小鸟
    {
        current_vx = 0;
        current_vy = 0;
    }

    move(wpos.x() + track_x , wpos.y() + track_y );     //移动小鸟
    if(wpos.x() + track_x > 1800 || wpos.y() + track_y  > 967 || wpos.y() + track_y < 0 ||
            wpos.x() + track_x < 0 || (current_vx == 0 && current_vy == 0  ))   //超过界面范围、速度为0重置小鸟
    {
        //move(wpos);
        move(70 , 620);
        timer->stop();
        time = 0;
        track_x = track_y = 0;
    }
    emit bird_move(QPoint(geometry().topLeft().x() + width()/2,
                          geometry().topLeft().y() + height()/2));


}

void bird::mouseMoveEvent(QMouseEvent *event)   //重写鼠标事件，时小鸟可拖动
{

    pos1 = event->globalPos();


    move(wpos.x()+pos1.x()-pos.x(),
         wpos.y()+pos1.y()-pos.y());
    emit bird_move(QPoint(geometry().topLeft().x() + width()/2,
                          geometry().topLeft().y() + height()/2));

}

void bird::mousePressEvent(QMouseEvent *event)
{
    flag_move = true;
    pos = event->globalPos();
    wpos = this->geometry().topLeft();

    if(event->buttons() ==  Qt::RightButton)
    {

        current_vx = current_vy = 0;
    }


}
//void bird::mouseReleaseEvent(QMouseEvent *event)
//{
//    flag_move = false;
//}

void bird::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.drawPixmap(0, 0, *pix);

}
