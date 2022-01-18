#include "Expression.h"
#include <iostream>

int main(){
    auto expr = sin(5.23333*X());
    std::cout<< expr.toString()<<std::endl;
    auto diff = expr.getDerivative();
    std::cout<<diff.toString()<<std::endl;
}