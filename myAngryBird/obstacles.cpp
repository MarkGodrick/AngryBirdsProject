#include "obstacles.h"
#include <QPixmap>
#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QTimer>

ObstAcles::ObstAcles(QString normalImg)
{
    ImagPath = normalImg;
    pix = new QPixmap;
    bool ret = pix->load(normalImg);
    if(!ret){
        qDebug() << "图片加载失败";
        return;
    }
    setFixedSize(pix->width(), pix->height());

    *pix = pix->scaled(pix->width() , pix->height() );
    setMask( pix->mask() );
    setMinimumHeight(pix->height());
    setMinimumWidth(pix->width());

    mid_width = pix->width();
    mid_height = pix->width();

    qDebug() << "obsacles " << "w " << mid_width << "h " << mid_height;

    mid_pos = new QPoint(pix->width() / 2, pix->height() / 2);
    //mid_pos = QPoint(pix->width() / 2, pix->height() / 2);

}

void ObstAcles::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.drawPixmap(0, 0, *pix);

}
