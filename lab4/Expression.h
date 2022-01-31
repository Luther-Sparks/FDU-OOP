#include <__bit_reference>
//
// Created by 王少文 on 2022/1/18.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "BaseExpr.h"
#include "UnaryOP.h"
#include "BinaryOP.h"

class Expression {
    friend Expression X();
    friend Expression sin(Expression operand);
    friend Expression cos(Expression operand);
    friend Expression operator-(Expression operand);
    friend Expression operator+(Expression left, Expression right);
    friend Expression operator-(Expression left, Expression right);
    friend Expression operator*(Expression left, Expression right);
    friend Expression operator/(Expression left, Expression right);
public:
    Expression(double value); // NOLINT
    Expression(BaseExpr* ptr); // NOLINT 让clang tidy闭嘴
    ~Expression(){
        delete ptr;
    }
    std::string toString() const;
    double evaluate() const;
    double evaluate(double x) const;
    Expression getDerivative() const;
private:
    BaseExpr* ptr;
};

Expression X();
Expression sin(Expression operand);
Expression cos(Expression operand);
Expression operator-(Expression operand);
Expression operator+(Expression left, Expression right);
Expression operator-(Expression left, Expression right);
Expression operator*(Expression left, Expression right);
Expression operator/(Expression left, Expression right);


#endif //EXPRESSION_H
