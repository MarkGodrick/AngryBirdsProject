#ifndef START_H
#define START_H

#include <QWidget>
#include "chooselevel.h"

class Start : public QWidget
{
    Q_OBJECT
public:
    explicit Start(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void start();//开始游戏，进入关卡选择界面
    void back();//返回上一个界面
public slots:

private:
    chooselevel *choose;
};

#endif // START_H

