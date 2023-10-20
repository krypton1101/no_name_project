#pragma once
#include "Point.h"
#include <vector>

namespace Physics
{
    class Object
    {
    private:
        float position[2];
        float rotation;
        std::vector <Point> points;
    public:
        Object();
    };
}