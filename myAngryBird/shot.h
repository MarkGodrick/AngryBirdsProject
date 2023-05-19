#ifndef SHOT_H
#define SHOT_H

#include <QWidget>
#include "bird.h"
#include "datacheck.h"
#include <QPoint>
#include <QTimer>

class slingshot : public QWidget
{
    Q_OBJECT

public slots:
    void slig(QPoint);

signals:
    void Releaseline();
    void back();//返回上一个界面


public:
    explicit slingshot(int xx, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    qreal vx;
    qreal vy;
    qreal resistance_const;
    qreal accg;



private:
    QPoint posline = QPoint(465, 551);//皮筋的起始位置
    bool pullflag = false;

    datacheck * check;

    bool flag;

};

#endif // WIDGET_H
