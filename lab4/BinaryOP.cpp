//
// Created by 王少文 on 2022/1/17.
//
#include "UnaryOP.h"
#include "BinaryOP.h"
#include "Operation.h"

double Addition::evaluate() const {
    return left->evaluate() + right->evaluate();
}

double Addition::evaluate(double x) const {
    return left->evaluate(x) + right->evaluate(x);
}

BaseExpr *Addition::getDerivative() const {
    return add(left->getDerivative(), right->getDerivative());
}

std::string Addition::toString() const {
    return "("+left->toString()+"+"+right->toString()+")";
}
BaseExpr *Addition::clone() const {
    return new Addition(left->clone(), right->clone());
}

double Subtraction::evaluate() const {
    return left->evaluate() - right->evaluate();
}

double Subtraction::evaluate(double x) const {
    return left->evaluate(x) - right->evaluate(x);
}

BaseExpr *Subtraction::getDerivative() const {
    return sub(left->getDerivative(),right->getDerivative());
}

std::string Subtraction::toString() const {
    return "("+left->toString()+"-"+right->toString()+")";
}
BaseExpr *Subtraction::clone() const {
    return new Subtraction(left->clone(), right->clone());
}

double Multiplication::evaluate() const {
    return left->evaluate() * right->evaluate();
}

double Multiplication::evaluate(double x) const {
    return left->evaluate(x) * right->evaluate(x);
}

BaseExpr *Multiplication::getDerivative() const {
    auto l = mul(left->getDerivative(),right);
    auto r = mul(left,right->getDerivative());
    return add(l,r);
}

std::string Multiplication::toString() const {
    return "("+left->toString()+"*"+right->toString()+")";
}

BaseExpr *Multiplication::clone() const {
    return new Multiplication(left->clone(), right->clone());
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

BaseExpr *Division::getDerivative() const {
    auto numerator = new Subtraction(new Multiplication(left->getDerivative(),right), new Multiplication(left, right->getDerivative()));
    auto denominator = new Multiplication(right,right);
    return div(numerator, denominator);
}

std::string Division::toString() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    return "("+left->toString()+"/"+right->toString()+")";
}

BaseExpr *Division::clone() const {
    return new Division(left->clone(), right->clone());
}