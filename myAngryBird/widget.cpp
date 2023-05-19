#pragma execution_character_set("utf-8")
#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>
//#include <QSqlQuery>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //界面主题设置
    setFixedSize(1874,1054);
    this->setWindowIcon(QIcon(":/img/red_bird.png"));
    this->setWindowTitle("进入游戏");

    log_in = new QPushButton("",this);
    log_in->setFlat(true);
    log_in->setStyleSheet("QPushButton{border:none;background:transparent;}");
    log_in->setFixedSize(346,246);
    log_in->setGeometry(720,800,346,246);
    //log_in->setIconSize(QSize(692,492));
    //log_in->setIcon(QIcon(":/img/test.png"));
    connect(log_in, SIGNAL(clicked(bool)), this, SLOT(login(bool)));// 绑定按钮bt_log 发射的clicked点击信号 给当前界面 的槽函数login

    //界面跳转
    start_ui = new Start;
    //choose = new choosepoint;
    connect(this, SIGNAL(login_successed()), start_ui, SLOT(show()));//绑定当前界面 发射的login_successed登录成功的信号 给游戏开始界面start_ui 让它显示

    connect(start_ui, &Start::back, this, [&](){
        this->setGeometry(start_ui->geometry());
        this->show();
    });//绑定游戏开始界面start_ui 发射的back返回信号 给当前界面 让它显示

}
void Widget::paintEvent(QPaintEvent *event)
{
    //画 界面 和 图标
    QPainter p(this);
    p.drawPixmap(0, 0, 1874, 1054, QPixmap(":/img/R-C.jpg"));
    p.drawPixmap(720, 800, 346, 246, QPixmap(":/img/test.png"));
}


void Widget::login(bool)
{
    emit login_successed();//发射登录成功的信号
    hide();//隐藏当前界面
    return ;

}
Widget::~Widget()
{

}
