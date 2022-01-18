#include "Expression.h"
#include "UnaryOP.h"
#include "BinaryOP.h"
#include <iostream>

int main(){
    auto x = variable();
    auto e = sin(x);
    auto ee = sin(cos(x));
    auto m = new Multiplication(ee, x);
    std::cout<< m->toString()<<std::endl;
    std::cout<<m->getDerivative()->toString()<<std::endl;



}