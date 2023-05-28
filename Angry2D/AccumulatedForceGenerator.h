#include"core_math.h"
using namespace std;
#define g 9.8
#define resist 0.4
class AccumForce
{
private:
    Vector AccumedForce;
public:
    AccumForce(Vector force = 0);
    void AddForce(Vector force);
    Vector getForce();
};
class CollisionGenerator
{
public:
CollisionGenerator(int m = 0) {}
};