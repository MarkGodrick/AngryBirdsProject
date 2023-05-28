#include<AccumulatedForceGenerator.h>
AccumForce::AccumForce(Vector force):AccumedForce(force)
{

}
void AccumForce::AddForce(Vector force)
{
    AccumedForce+=force;
}
Vector AccumForce::getForce()
{
    return AccumedForce;
}