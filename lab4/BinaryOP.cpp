//
// Created by 王少文 on 2022/1/17.
//

#include "BinaryOP.h"

double Addition::evaluate() const {
    return left->evaluate() + right->evaluate();
}

double Addition::evaluate(double x) const {
    return left->evaluate(x) + right->evaluate(x);
}

Expression *Addition::getDerivative() const {
    return new Addition(left->getDerivative(), right->getDerivative());
}

std::string Addition::toStringRaw() const {
    //至少左边或者右边有一个存在变量
    if(left->alwaysZero()){//左边没有变量且始终为0
        return right->toString();
    }
    if(right->alwaysZero()){//右边没有变量且始终为0
        return left->toString();
    }
    return "("+left->toString()+"+"+right->toString()+")";
}


double Subtraction::evaluate() const {
    return left->evaluate() - right->evaluate();
}

double Subtraction::evaluate(double x) const {
    return left->evaluate(x) - right->evaluate(x);
}

Expression *Subtraction::getDerivative() const {
    return new Subtraction(left->getDerivative(),right->getDerivative());
}

std::string Subtraction::toStringRaw() const {
    if(left->alwaysZero()){//左边恒为0
        return "(-"+right->toString()+")";
    }
    if(right->alwaysZero()){
        return left->toString();
    }
    return "("+left->toString()+"-"+right->toString()+")";
}


double Multiplication::evaluate() const {
    return left->evaluate() * right->evaluate();
}

double Multiplication::evaluate(double x) const {
    return left->evaluate(x) * right->evaluate(x);
}

Expression *Multiplication::getDerivative() const {
    auto l = new Multiplication(left->getDerivative(),right);
    auto r = new Multiplication(left,right->getDerivative());
    return new Addition(l,r);
}

std::string Multiplication::toStringRaw() const {
    if(left->alwaysZero()||right->alwaysZero()){
        return "0";
    }
    if(!left->hasVariable()&&left->evaluate()==1){
        return right->toString();
    }
    if(!right->hasVariable()&&right->evaluate()==1){
        return left->toString();
    }
    return "("+left->toString()+"*"+right->toString()+")";
}


double Division::evaluate() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    return left->evaluate() / right->evaluate();
}

double Division::evaluate(double x) const {
    if(right->evaluate(x) == 0){
        throw std::runtime_error("Divided by zero error");
    }
    return left->evaluate(x) / right->evaluate(x);
}

Expression *Division::getDerivative() const {
    auto numerator = new Subtraction(new Multiplication(left->getDerivative(),right), new Multiplication(left, right->getDerivative()));
    auto denominator = new Multiplication(right,right);
    return new Division(numerator, denominator);
}

std::string Division::toStringRaw() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    if(left->alwaysZero()){
        return "0";
    }
    return "("+left->toString()+"/"+right->toString()+")";
}





