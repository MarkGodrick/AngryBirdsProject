#ifndef STARTBIRD_H
#define STARTBIRD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
class startbird : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal birdx READ birdx WRITE setbirdX)
public:
    explicit startbird(QObject *parent = nullptr);
    ~startbird();
    qreal birdx() const;
    void wings();
    QPropertyAnimation* birdani;

public slots:
    void setbirdX(qreal x);
    void sbirdstop();private:    //QGraphicsPixmapItem(QPixmap(":/ground.png"))
    qreal bird_x;
    bool wingdirect;    //0 down 1 up
    int wingpos;        //0 up 1 middle 2 down};
signals:

};

#endif // STARTBIRD_H
