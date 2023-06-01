#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include "scene.h"
#include<QLabel>
#include<birditem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    friend class Scene;
    void showblock();
    QTimer *timer;
    QTimer *timer1;
    QGraphicsPixmapItem* get_ready;
    QGraphicsPixmapItem* count[3];
    int cnter = 0;
public slots:
    void score_update();
    void check_over();
    void start_ticking();
    void gamebegin();
    void rcount();
private:
    Ui::Widget *ui;
    Scene* scene;
signals:
    void begin();
    void end();
};
#endif // WIDGET_H
