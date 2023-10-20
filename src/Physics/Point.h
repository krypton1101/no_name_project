#pragma once

namespace Physics
{
    class Point
    {
    private:
        float position[2];
        unsigned int type;
        int mass;
    public:
        Point(int mass = 0, unsigned int type = 0): mass(mass), type(type) {}
        ~Point() = default;

        void setPosition(float x, float y);
        void getPosition(float& x, float& y);
        int getMass();
        unsigned int getType();
    };
}