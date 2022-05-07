#include <iostream>

int main(){
    auto expr = sin(5.23333*X()) + 1/X();
    std::cout<< expr.toString()<<std::endl;
    auto diff = expr.getDerivative();
    std::cout << diff.toString() << std::endl;
    std::cout << diff.evaluate(1.0) << std::endl;
}