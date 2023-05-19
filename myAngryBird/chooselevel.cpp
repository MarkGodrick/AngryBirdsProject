#pragma execution_character_set("utf-8")
#include "chooselevel.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include "mybushbutton.h"
#include <QMessageBox>
#include <QTimer>
#include <QLabel>


chooselevel::chooselevel(QWidget *parent) : QMainWindow(parent)
{
    //选择关卡场景
    this->setFixedSize(1800, 967);
    setGeometry(750, 420,1800,967);
    this->setWindowIcon(QIcon(":/img/icon.png"));
    this->setWindowTitle("关卡场景");
    //返回按钮
    mybushbutton * backbtn = new mybushbutton(":/img/BackButton.png",":/img/BackButtonSelected.png");

    backbtn->setParent(this);
    backbtn->move(1713, 10);
    //跳转到上一个界面
    connect(backbtn, &mybushbutton::clicked,[=](){
            QTimer::singleShot(300,this,[=](){
            emit this->choosesceneback(); //为了看到动画效果
            hide();
        });
    });
    int i;
    //跳转到关卡界面   创建选择关卡的按钮
    for( i = 0; i < 20; i++)
    {
        mybushbutton * menubtn = new mybushbutton(":/img/LevelIcon.png");

        menubtn->setParent(this);
        menubtn->move( 560 + i % 5 * 160, 300 + i / 5 * 130);  //一维数构造二维数组
        if(i < 3)
        {
            connect(menubtn, &mybushbutton::clicked,[=](){

                this->hide();//隐藏当前界面
                    //界面跳转
                    shot = new slingshot(i + 1);
                    shot->setGeometry(this->geometry());
                    shot->show();
                    //设置游戏场景初始位置
                    //监听返回
            connect(shot, &slingshot::back, this, [=](){

                    this->setGeometry(shot->geometry());

                    shot->deleteLater();
                    this->show();

                });//
            });
        }
        else
        {

            connect(menubtn,&mybushbutton::clicked,[&](){
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon(":/img/red_bird.png"));
                msgBox.setIconPixmap(QPixmap(":/img/icon.png"));
                msgBox.setText("该关卡未解锁");
                if( QMessageBox::Yes == msgBox.exec())
                {
                    QTimer::singleShot(300,this,[=](){
                    //emit this->choosesceneback(); //为了看到动画效果
                    hide();});
                }
            });
        }
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        //qDebug(" %d%d",menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(560 + i % 5 * 160, 300 + i / 5 * 130);

        //设置label上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt:: AlignVCenter);
        //设置鼠标穿透事件  51号
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}
//重写绘图事件
void chooselevel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //加载图片
    pix.load(":/img/choose.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}


