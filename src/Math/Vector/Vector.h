#pragma once
#include <vector>

namespace Math
{
    template <typename T>
    class Vector
    {
    private:
        std::vector<T> vec;
    public:
        Vector();
        ~Vector();
        Vector operator+(Vector);
        Vector operator-(Vector);
        template <typename K>
            Vector operator*(K);
        T operator[](int);
    };
}