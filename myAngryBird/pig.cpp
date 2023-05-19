#include "pig.h"
#include <QPainter>
#include <QTimer>
#include <QPixmap>

pig::pig()
{
    setFixedSize(64, 64);
    mid_pos = new QPoint(32, 32);

}
void pig::paintEvent(QPaintEvent *event)
{

     QPainter p1(this);
//     if(isboom)
//     {
//         QPainter p(pp);
//         p.drawPixmap(0, 0, 64,64, QPixmap(":/img/boom.png"));
//     }
//     else
        p1.drawPixmap(0, 0, 64,64, QPixmap(":/img/pig.png"));
}
void pig::boom( pig *p)
{
    isboom = true;
    //pp = p;
    update();

    QTimer::singleShot(200,this,[=](){
         p->hide();
    });
}
