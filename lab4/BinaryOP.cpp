//
// Created by 王少文 on 2022/1/17.
//
#include "UnaryOP.h"
#include "BinaryOP.h"

double Addition::evaluate() const {
    return left->evaluate() + right->evaluate();
}

double Addition::evaluate(double x) const {
    return left->evaluate(x) + right->evaluate(x);
}

BaseExpr *Addition::getDerivative() const {
    return add(left->getDerivative(), right->getDerivative());
}

std::string Addition::toStringRaw() const {
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

std::string Subtraction::toStringRaw() const {
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

std::string Multiplication::toStringRaw() const {
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

std::string Division::toStringRaw() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    return "("+left->toString()+"/"+right->toString()+")";
}

BaseExpr *Division::clone() const {
    return new Division(left->clone(), right->clone());
}

BaseExpr* add(BaseExpr* left, BaseExpr* right){
    if(left->alwaysZero()&&right->alwaysZero()){
        return new Constant(0);
    }
    if(!left->alwaysZero()&&right->alwaysZero()){
        return left->clone();
    }
    if(left->alwaysZero()&&!right->alwaysZero()){
        return right->clone();
    }
    return new Addition(left->clone(),right->clone());
}
BaseExpr* sub(BaseExpr* left, BaseExpr* right){
    if(left->alwaysZero()&&right->alwaysZero()){
        return new Constant(0);
    }
    if(!left->alwaysZero()&&right->alwaysZero()){
        return left->clone();
    }
    if(left->alwaysZero()&&!right->alwaysZero()){
        return new Minus(right);
    }
    return new Subtraction(left->clone(),right->clone());
}
BaseExpr* mul(BaseExpr* left, BaseExpr* right){
    if(left->alwaysZero()||right->alwaysZero()){
        return new Constant(0);
    }
    if((!left->hasVariable()&&left->evaluate()==1)&&(!right->hasVariable()&&right->evaluate()==1)){
        return new Constant(1);
    }
    if(!left->hasVariable()&&left->evaluate()==1){
        return right->clone();
    }
    if(!right->hasVariable()&&right->evaluate()==1){
        return left->clone();
    }
    return new Multiplication(left->clone(),right->clone());
}
BaseExpr* div(BaseExpr* left, BaseExpr* right){
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    if(left->alwaysZero()){
        return new Constant(0);
    }
    return new Division(left->clone(), right->clone());
}



