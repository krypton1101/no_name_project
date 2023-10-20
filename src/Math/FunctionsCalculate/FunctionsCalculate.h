#include "Vector.h"
#pragma once

namespace Math
{
    // Функция счета позиции через единицу времени
    template <typename T>
    std::vector<T> TickfullPositionCalculation(std::vector<T> currentPositionVector,
                            std::vector<T> speedVector,
                            std::vector<T> accelerationVector);

    // Функция счета позиции в кокретный момент времени (в т.ч. дробный)
    // На вход - вектор-позиция и вектор-ускорение, количество элементов кратное кол-ву эл-тов вектор-позиции и момент времени.
    template <typename T>
    std::vector<T> TicklessPositionCalculation(std::vector<T> currentPosition,
                            std::vector<T> speedVector,
                            std::vector<T> accelerationVector,
                            double time);

    // Перегрузка с использованием вектора функций - счетчиков ускорения
    template <typename T>
    std::vector<T> TicklessPositionCalculation(std::vector<T> currentPosition,
                            std::vector<T> speedVector,
                            std::vector<T (*)(double)> accelerationFunctionsVector,
                            double time);
}