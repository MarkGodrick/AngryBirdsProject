#include"rigidbody.h"
object::object(real m,real xPos,real yPos,real dir = 0):mass(m),inverse_mass(1/m),pos(xPos,yPos),theta(0),v(0),omega(0),a(0),beta(0)
{

}
void Circle::simulate(AccumForce F)
{
    //如果没有碰撞
    if(result==0)
    {
        pos+=v*FRAME_TIME;
        v+=a*FRAME_TIME;
        a+=F.getForce()*FRAME_TIME*inverse_mass;
        theta+=omega*FRAME_TIME;
        if(pos.y-R<level)
        {
            pos.y=level+R;
        }
    }
}
void Stick::simulate(AccumForce F)
{
    if(result==0)
    {
        pos+=v*FRAME_TIME;
        v+=a*FRAME_TIME;
        a+=F.getForce()*FRAME_TIME*inverse_mass;
        theta= theta+ omega*FRAME_TIME;
        while(theta>2*PI)
        {
            theta=theta-2*PI;
        }

    }
}
