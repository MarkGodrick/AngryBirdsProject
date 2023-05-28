#ifndef WORLD_H
#define WORLD_H
#include<vector>
#include"rigidbody.h"
#include"core_math.h"
class world
{
public:
    int circle_num;
    int rectangle_num;
    real floor_level;
    vector slingshot;
    // 破掉的材料和挂掉的猪猪，作为积分值的判定
    int brokensticks;
    int deadpigs;
    vector<Circle> circles;
    vector<Stick> sticks;
    //一个关卡的初始化，传入的参数不止3个
    world(int c,int r,int f);
    void detect();
    void simulate();
    // 用拉开弹弓时的(x,y)坐标作为开始进行计算，直到所有事物静止后停止模拟
    //
    void one_shot(real x,real y);
};

#endif // WORLD_H
