#include "UnaryOP.h"

#include <cmath>

#include "BinaryOP.h"

BaseExpr* UnaryOP::getDerivative() const {
    return mul(operand->getDerivative(), getDerivativeOuter());
}

std::string Sin::toString() const {
    return "sin(" + operand->toString() + ")";
}
double Sin::evaluate() const { return sin(operand->evaluate()); }
double Sin::evaluate(double x) const { return sin(operand->evaluate(x)); }
BaseExpr* Sin::getDerivativeOuter() const { return cos(operand); }
BaseExpr* Sin::clone() const { return new Sin(operand->clone()); }

std::string Cos::toString() const {
    return "cos(" + operand->toString() + ")";
}
double Cos::evaluate() const { return cos(operand->evaluate()); }
double Cos::evaluate(double x) const { return cos(operand->evaluate(x)); }
BaseExpr* Cos::getDerivativeOuter() const { return minus(sin(operand)); }
BaseExpr* Cos::clone() const { return new Cos(operand->clone()); }

double Minus::evaluate() const { return -1 * operand->evaluate(); }
double Minus::evaluate(double x) const { return -1 * operand->evaluate(x); }
std::string Minus::toString() const {
    return "(-" + operand->toString() + ")";
}
BaseExpr* Minus::getDerivativeOuter() const { return new Constant(-1); }
BaseExpr* Minus::clone() const { return new Minus(operand->clone()); }
