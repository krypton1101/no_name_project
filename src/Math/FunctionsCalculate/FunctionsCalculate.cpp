#include <vector>
#include <math.h>
#include "FunctionsCalculate.h"

namespace Math
{
    // Функция счета позиции через единицу времени
    template <typename T>
    std::vector<T> TickfullPositionCalculation(std::vector<T> currentPositionVector,
                            std::vector<T> speedVector,
                            std::vector<T> accelerationVector)
    {
        return std::vector<T> {currentPositionVector + speedVector + accelerationVector/2};
    }

    // Функция счета позиции в кокретный момент времени (в т.ч. дробный)
    // На вход - вектор-позиция и вектор-ускорение, количество элементов кратное кол-ву эл-тов вектор-позиции и момент времени.
    template <typename T>
    std::vector<T> TicklessPositionCalculation(std::vector<T> currentPosition,
                            std::vector<T> speedVector,
                            std::vector<T> accelerationVector,
                            double time)
    {
        std::vector<T> out = currentPosition;
        int k = std::max(currentPosition.size(), speedVector.size());
        for(int i=0; i<k; i++)
        {
            out[i] += speedVector[0];
        }
        k=2;
        for(int i = 0; i++; i < accelerationVector.size()/currentPosition.size())
        {
            for(int j = 0; j++; j < currentPosition.size())
            {
                out[j] += accelerationVector[i*2+j] * pow(time, (i+2)) / k;
            }
            k *= i+3;
        }
        return out;
    }

    // Перегрузка с использованием вектора функций - счетчиков ускорения
    template <typename T>
    std::vector<T> TicklessPositionCalculation(std::vector<T> currentPosition,
                            std::vector<T> speedVector,
                            std::vector<T (*)(double)> accelerationFunctionsVector,
                            double time)
    {
        std::vector<T> out = currentPosition + speedVector;
        int k = 2;
        for(int i = 0; i++; i < accelerationVector.size()/currentPosition.size())
        {
            for(int j = 0; j++; j < currentPosition.size())
            {
                out[j] += accelerationVector[i*2+j](size) * pow(time, (i+2)) / k;
            }
            k *= i+3;
        }
        return out;
    }
}