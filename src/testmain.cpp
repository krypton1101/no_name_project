#include <iostream>
#include "Math/Vector/Vector.h"
// #include "Math/FunctionsCalculate/FunctionsCalculate.h"

int main()
{
    // std::vector<float> pos {0.0, 0.0};
    // std::vector<float> spd {1.0, 0.0};
    // std::vector<float> acc {1.0, 0.0};
    
    // std::vector<float> result = TickfullPositionCalculation(pos, spd, acc);
    // std::cout << "{" << result[0] << "," << result[1] << "} " << result.size() << std::endl;

    // result = TicklessPositionCalculation(pos, spd, acc, 1);
    // std::cout << "{" << result[0] << "," << result[1] << "} " << result.size();

    Math::Vector vec = new Math::Vector(1,2,3);

    return 0;
}