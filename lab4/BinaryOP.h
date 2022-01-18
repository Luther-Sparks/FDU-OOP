//
// Created by 王少文 on 2022/1/17.
//

#ifndef BINARY_OP_H
#define BINARY_OP_H
#include "Expression.h"

class BinaryOP : public Expression {
   public:
    BinaryOP(Expression *left, Expression *right) : left(left), right(right) {}
    ~BinaryOP() override {
        delete left;
        delete right;
    }
    bool hasVariable() const final {
        return left->hasVariable() || right->hasVariable();
    }

    double evaluate() const override = 0;

    double evaluate(double x) const override = 0;

    Expression *getDerivative() const override = 0;


protected:
    Expression *left;
    Expression *right;
    std::string toStringRaw() const override = 0;
};

class Addition final : public BinaryOP{
public:
    Addition(Expression *left, Expression *right): BinaryOP(left, right){}
    ~Addition() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    Expression *getDerivative() const override;
    std::string toStringRaw() const override;
};

class Subtraction final : public BinaryOP{
public:
    Subtraction(Expression *left, Expression *right): BinaryOP(left, right){}
    ~Subtraction() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    Expression *getDerivative() const override;
    std::string toStringRaw() const override;
};

class Multiplication final :public BinaryOP{
public:
    Multiplication(Expression *left, Expression *right): BinaryOP(left, right){}
    ~Multiplication() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    Expression *getDerivative() const override;
    std::string toStringRaw() const override;
};

class Division final: public BinaryOP{
public:
    Division(Expression *left, Expression *right): BinaryOP(left, right){}
    ~Division() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    Expression *getDerivative() const override;
    std::string toStringRaw() const override;
};



#endif  // BINARY_OP_H
