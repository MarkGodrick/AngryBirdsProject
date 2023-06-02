#include "widget.h"
#include "ui_widget.h"
#include "pipeitem.h"
#include "birditem.h"
#include<scene.h>
#include "ground.h"
#include <QGraphicsPixmapItem>
#include<QTime>
#include<QLabel>
#include<QImage>
#include<QIcon>
#include<QPixmap>
#include<QPushButton>
#include<QSize>
#include<startbird.h>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("FlappyBird");
    setWindowIcon(QIcon(":/0.png"));
    scene = new Scene(this);
    scene->setSceneRect(0,0,432,644);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->pushButton->setFixedSize(130,50);
    ui->pushButton->setGeometry(151,360,130,50);
    ui->pushButton->setIcon(QPixmap(":/startbutton.png"));
    ui->pushButton->setIconSize(QSize(130,50));
    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(QPixmap(":/bg.png"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0));
    ui->Box->setScene(scene);
    timer = new QTimer(this);

    get_ready = new QGraphicsPixmapItem(QPixmap(":/get_ready.png"));

    for(int i = 0; i < 3; ++i)
    {
        switch(i)
        {
        case 0:
            count[i]=new QGraphicsPixmapItem(QPixmap(":/num1.png"));
            break;
        case 1:
            count[i]=new QGraphicsPixmapItem(QPixmap(":/num2.png"));
            break;
        case 2:
            count[i]=new QGraphicsPixmapItem(QPixmap(":/num3.png"));
            break;
        }

    }
    connect(ui->pushButton,&QPushButton::clicked,this,[&]()
    {
        scene->birdi->groundstop();
        scene->removeItem(scene->birdi);
        scene->removeItem(scene->startImage);
        delete scene->startImage;
        delete scene->birdi;
        qDebug("%d",scene->clickcnt);
        ui->pushButton->hide();
        emit begin();
    });

    connect(this,SIGNAL(begin()),this,SLOT(start_ticking()));
    connect(timer,SIGNAL(timeout()),this,SLOT(score_update()));
    connect(timer,SIGNAL(timeout()),this,SLOT(check_over()));

}
Widget::~Widget()
{
    delete ui;
}

void Widget::score_update()
{
    QFont font("Consolas",10,50);
    QString score= QString::number(scene->score);
    ui->label->setFont(font);
    this -> ui->label->setText("score: "+score);
    ui->label->show();

}
void Widget::check_over()
{
    if(scene->gameoverbool)
    {
       ui->label->hide();
    }
}

void Widget::start_ticking()
{
    scene->addItem(get_ready);
    get_ready->setPos(118,180);
    timer1 = new QTimer(this);
    timer1->start(1000);
    connect(timer1,SIGNAL(timeout()),this,SLOT(rcount()));
    connect(this,SIGNAL(end()),this,SLOT(gamebegin()));
}

void Widget::rcount()
{
    if(cnter != 0)
    {
        scene->removeItem(count[3 - cnter]);
        delete count[3 - cnter];
    }
    if(cnter<3)
    {
        scene->addItem(count[2 - cnter]);
        count[2 - cnter]->setPos(208,280);
    }
    if(cnter==3)
    {
        timer1->stop();
        emit end();
    }
    cnter++;
    return;
}

void Widget::gamebegin()
{
    scene->removeItem(get_ready);
    delete get_ready;
    scene->mainstart();
    connect(scene->bird,&birditem::collidesignal2,[=](){
        scene->gameover();
     });
    timer->start(100);
}

