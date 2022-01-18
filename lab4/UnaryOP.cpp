#include "UnaryOP.h"
#include "BinaryOP.h"
#include <cmath>

BaseExpr *UnaryOP::getDerivative() const {
    return mul(operand->getDerivative(), getDerivativeRaw());
}

std::string Sin::toStringRaw() const {return "sin(" + operand->toString()+ ")";}
double Sin::evaluate() const { return sin(operand->evaluate()); }
double Sin::evaluate(double x) const { return sin(operand->evaluate(x)); }
BaseExpr* Sin::getDerivativeRaw() const {
    return new Cos(operand);
}

std::string Cos::toStringRaw() const { return "cos(" + operand->toString() + ")"; }
double Cos::evaluate() const { return cos(operand->evaluate()); }
double Cos::evaluate(double x) const { return cos(operand->evaluate(x)); }
BaseExpr* Cos::getDerivativeRaw() const {
    return new Minus(new Sin(operand));
}

double Minus::evaluate() const {
    return -1*operand->evaluate();
}
double Minus::evaluate(double x) const {
    return -1*operand->evaluate(x);
}
std::string Minus::toStringRaw() const {
    return "(-"+operand->toString()+")";
}
BaseExpr *Minus::getDerivativeRaw() const {
    return new Constant(-1);
}
