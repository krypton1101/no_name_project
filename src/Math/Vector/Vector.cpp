#include "Vector.h"

namespace Math
{
    template <typename T>
    Vector Vector::operator+(Vector OpVec)
    {

    }

    template <typename T>
    Vector Vector::operator-(Vector OpVec)
    {

    }

    template <typename T, typename K>
    Vector Vector::operator*(K OpValue)
    {
        
    }

    template <typename T>
    T Vector::operator[](int index)
    {
        return vec.at(index);
    }

}