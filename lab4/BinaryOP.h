//
// Created by 王少文 on 2022/1/17.
//

#ifndef BINARY_OP_H
#define BINARY_OP_H
#include "BaseExpr.h"

class BinaryOP : public BaseExpr {
   public:
    BinaryOP(BaseExpr *left, BaseExpr *right) : left(left), right(right) {}
    ~BinaryOP() override {
        delete left;
        delete right;
    }
    bool hasVariable() const final {
        return left->hasVariable() || right->hasVariable();
    }

    double evaluate() const override = 0;

    double evaluate(double x) const override = 0;

    BaseExpr *getDerivative() const override = 0;


protected:
    BaseExpr *left;
    BaseExpr *right;
    std::string toStringRaw() const override = 0;
};

class Addition final : public BinaryOP{
public:
    Addition(BaseExpr *left, BaseExpr *right): BinaryOP(left, right){}
    ~Addition() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr *getDerivative() const override;
    std::string toStringRaw() const override;
    BaseExpr *clone() const final;
};

class Subtraction final : public BinaryOP{
public:
    Subtraction(BaseExpr *left, BaseExpr *right): BinaryOP(left, right){}
    ~Subtraction() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr *getDerivative() const override;
    std::string toStringRaw() const override;
    BaseExpr *clone() const final;
};

class Multiplication final :public BinaryOP{
public:
    Multiplication(BaseExpr *left, BaseExpr *right): BinaryOP(left, right){}
    ~Multiplication() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr *getDerivative() const override;
    std::string toStringRaw() const override;
    BaseExpr *clone() const final;
};

class Division final: public BinaryOP{
public:
    Division(BaseExpr *left, BaseExpr *right): BinaryOP(left, right){}
    ~Division() final = default;
    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr *getDerivative() const override;
    std::string toStringRaw() const override;
    BaseExpr *clone() const final;
};

BaseExpr* add(BaseExpr* left, BaseExpr* right);
BaseExpr* sub(BaseExpr* left, BaseExpr* right);
BaseExpr* mul(BaseExpr* left, BaseExpr* right);
BaseExpr* div(BaseExpr* left, BaseExpr* right);


#endif  // BINARY_OP_H
