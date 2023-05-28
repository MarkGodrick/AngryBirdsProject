#include "core_math.h"
#include "AccumulatedForceGenerator.h"
#include<string.h>
using namespace std;
// 框架的刷新时间
// 窗口的坐标系的总长度
// 窗口坐标系的总高度
#define FRAME_TIME 0.01
#define FRAME_LENGTH 100
#define FRAME_HIEGHT 50
#define PI 3.146
#define level 5
//整形数据备用
typedef int integer;
class object
{
public:
    real mass;
    //逆质量，用来算加速度
    real inverse_mass;
    //质心的位置
    Vector pos;
    //刚体的方向 θ
    Angle theta;
    //质心的速度
    Vector v;
    //刚体的角速度 ω
    Vector omega;
    //质心的加速度
    Vector a;
    //刚体的角加速度 β
    Vector beta;
    //受力分析结果:0 表示空中的(无接触),1 表示有接触但是没碰撞，2 表示有碰撞
    int result;
    object(real m,real xPos,real yPos,real dir = 0);
};
class Circle:public object
{
public:
    real R;
    Circle(real m,real xPos,real yPos,real dir = 0,real radius);
    //在没有和任何物体相撞的情况下模拟运算一次
    void simulate(AccumForce F);
};
class Stick:public object
{
public:
    real length;real width;
    real R;//接触检测半径
    Stick(real m,real xPos,real yPos,real dir = 0,real l,real w);
    void simulate(AccumForce F);
}
