#include "core_math.h"
Angle::Angle(real m = 0):theta(m) {}
Angle::operator real()
{
    return theta;
}
Angle Angle::operator+(Angle temp)
{
    return Angle(theta+temp.theta);
}
Vector::Vector(int m = 0,int n = 0):x(m),y(n) {}
Vector::Vector(real m,real n):x(m),y(n) {}
Vector::Vector(real len,Angle a)
{
    x = len*cos(a);
    y = len*sin(a);
}
Vector Vector::operator+(const Vector v)
{
    return Vector(x+v.x,y+v.y);
}
void Vector::operator+=(const Vector v)
{
    x+=v.x;y+=v.y;
}
Vector Vector::operator-(const Vector v)
{
    return Vector(x-v.x,y-v.y);
}
void Vector::operator-=(const Vector v)
{
    x-=v.x;y-=v.y;
}
//分量积
Vector Vector::componentProduct(Vector v)
{
    return Vector(x*v.x,y*v.y);
}
void Vector::componentProductUpdate(const Vector &vector)
{
    x *= vector.x;
    y *= vector.y;
}
//点积
real Vector::operator*(Vector v)
{
    return x*v.x+y*v.y;
}
//向量积
real Vector::operator%(Vector v)
{
    return (x*v.y-y*v.x);
}
//数乘
Vector Vector::operator*(int t)
{
    return Vector(t*x,t*y);
}
Vector Vector::operator*(real t)
{
    return Vector(t*x,t*y);
}
Vector Vector::addScaledVector(Vector v,int t)
{
    return Vector(x+t*v.x,y+t*v.y);
}