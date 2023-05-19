#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
//#include <QSqlDatabase>
#include <QLineEdit>
#include <QGroupBox>
#include "start.h"

class Widget : public QWidget
{
    Q_OBJECT
signals:
    void login_successed();//发射登录成功的信号，用来触发跳转到下一个界面
public slots:
    //void regiser(bool);
    void login(bool);

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    //void mousePressEvent(QMouseEvent *event);


private:
    QPushButton *log_in;

    bool show_key = true;

    QWidget *box;
    //QSqlDatabase db;

    Start *start_ui;
   // choosepoint *choose;
};

#endif // WIDGET_H
