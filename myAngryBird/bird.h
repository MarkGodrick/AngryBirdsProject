#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QtMath>
#include <QDebug>
class bird : public QWidget
{
    Q_OBJECT
public slots:
    void port(qreal vx, qreal vy, qreal resistance_const, qreal accg);  //x， y方向速度， 空气阻力常速， 重力加速度

public:
    explicit bird(QString normalImg);
    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

//    void mouseReleaseEvent(QMouseEvent *event);

     QPoint *mid_pos;
     int mid_width;
     int mid_height;

     qreal current_vy = 0;
     qreal current_vx = 0; //当前鸟的速度
     qreal resistance_const = 0;
     qreal accg = 0;
     QTimer *timer;

    bool flag_move;

    bool flag ;
signals:
      void clicked(qreal,qreal,qreal,qreal);
      void botton_clicek(int );
      void bird_move(QPoint);
private:
      int heavy;
      QPixmap *pix;
      QString ImagPath;

      QPoint pos;
      QPoint pos1;
      QPoint wpos;
      int energy = 0;

      qreal last_vx = 0;

      qreal bird_weight;    //鸟的重量

      qreal track_x = 0;    //x方向的运动轨迹
      qreal track_y = 0;    //y反向运动轨迹
      qreal last_y = 0;

      qreal resistance_ax = 0;  //x方向的空气阻力加速度
      qreal resistance_ay = 0;  //y方向的空气阻力加速度
      float time;


      bool vx_flag ;




};

#endif // BIRD_H
