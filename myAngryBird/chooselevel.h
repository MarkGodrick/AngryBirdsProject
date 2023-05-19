#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include "shot.h"
class chooselevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevel(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //void mousePressEvent(QMouseEvent *event);

signals:
    void choosesceneback();//返回上一个界面
    void level_1();//进入关卡 1

private:
    slingshot *shot;
};

#endif
