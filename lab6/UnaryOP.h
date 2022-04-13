#ifndef UNARY_OP_H
#define UNARY_OP_H

#include "BaseExpr.h"
#include "Operation.h"

class UnaryOP : public BaseExpr {
   public:
    explicit UnaryOP(BaseExpr* operand) : operand(operand) {}
    ~UnaryOP() override { delete operand; }
    bool hasVariable() const final { return operand->hasVariable(); }

    double evaluate() const override = 0;
    double evaluate(double x) const override = 0;
    BaseExpr* getDerivative() const override;

   protected:
    BaseExpr* operand;
    virtual BaseExpr* getDerivativeOuter() const = 0;
};

class Sin final : public UnaryOP {
   public:
    explicit Sin(BaseExpr* operand) : UnaryOP(operand) {}
    ~Sin() override = default;

    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr* clone() const override;

   protected:
    std::string toString() const override;
    BaseExpr* getDerivativeOuter() const override;
};

class Cos final : public UnaryOP {
   public:
    explicit Cos(BaseExpr* operand) : UnaryOP(operand) {}
    ~Cos() override = default;

    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr* clone() const override;

   protected:
    std::string toString() const override;
    BaseExpr* getDerivativeOuter() const override;
};

class Minus final : public UnaryOP {
   public:
    explicit Minus(BaseExpr* operand) : UnaryOP(operand) {}
    ~Minus() override = default;

    double evaluate() const override;
    double evaluate(double x) const override;
    BaseExpr* clone() const override;

   protected:
    std::string toString() const override;
    BaseExpr* getDerivativeOuter() const override;
};
#endif
