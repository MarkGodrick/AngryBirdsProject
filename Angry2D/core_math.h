/*
Math part
*/
#include<math.h>
#define real double
class Angle
{
public:
    real theta;
    Angle(real m = 0);
    operator real();
    Angle operator+(Angle temp);
    bool operator<(int temp);
    bool operator<(Angle temp);
    bool operator<=(int temp);
    bool operator<=(Angle temp);
    bool operator>=(int temp);
    bool operator>=(Angle temp);
    bool operator>(int temp);
    bool operator>(Angle temp);
    bool operator==(int temp);
    bool operator==(Angle temp);
};
class Vector
{
public:
    real x;
    real y;
    Vector(int m = 0,int n = 0);
    Vector(real m,real n);
    Vector(real len,Angle a);
    Vector operator+(const Vector v);
    void operator+=(const Vector v);
    Vector operator-(const Vector v);
    void operator-=(const Vector v);
    Vector componentProduct(Vector v);
    void componentProductUpdate(const Vector &vector);
    //点积
    real operator*(Vector v);
    //向量积
    real operator%(Vector v);
    //数乘
    Vector operator*(int t);
    Vector operator*(real t);
    Vector addScaledVector(Vector v,int t);
    real distance(Vector a,Vector b);
};
