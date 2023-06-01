#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include "birditem.h"
#include<QPixmap>

class groundItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal groundx READ groundx WRITE setgroundx)
    qreal m_groundx;

public:
    explicit groundItem(QObject *parent = nullptr);
    groundItem(QString,QObject *parent = nullptr);
    qreal groundx() const;
    //地面当前位置
    QPropertyAnimation* groundani;
    //让地面从右往左进行移动
    bool wingdirect;    //0 down 1 up
    int wingpos;        //0 up 1 middle 2 down
    void wings();
public slots:
    void setgroundx(qreal groundx);
    void groundstop();

signals:
};

#endif // GROUND_H
