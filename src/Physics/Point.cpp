#include "Point.h"

namespace Physics
{
    int Point::getMass()
    {
        return mass;
    }
    void Point::getPosition(float& x, float&y)
    {
        x = position[0];
        y = position[1];
    }
    unsigned int Point::getType()
    {
        return type;
    }
    void Point::setPosition(float x, float y)
    {
        position[0] = x;
        position[1] = y;
    }
}