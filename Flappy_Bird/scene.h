#ifndef SCENE_H
#define SCENE_H

#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <birditem.h>
#include "pipeitem.h"
#include "ground.h"
#include <QGraphicsPixmapItem>
#include<QWidget>
#include<QGraphicsSceneMouseEvent>
#include<QKeyEvent>
#include<startbird.h>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void birddef();
    void mainstart();
    void Scoreadd();
    bool gameoverbool;
    QGraphicsPixmapItem* startImage;
    birditem* bird;
    groundItem* birdi;
    int clickcnt = 0;
    void gameover();
signals:

private:
    void setpipetimer();
    QTimer* pipetimer;
    QGraphicsPixmapItem* gameoverImage;
    bool startsign;

    groundItem* ground;

    QGraphicsTextItem* scoretext;
    void showscore();
public slots:
    // QGraphicsScene interface
protected:
    //void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    int score;
};

#endif // SCENE_H
