#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <stdexcept>
#include <string>
/**
 * @brief Expression是抽象表达式基类，定义了表达式的接口。
 * 所有的表达式都必须继承自Expression，共有四类：
 * 1. 常量表达式：Constant，是double型的常数，如1, 2.3
 * 2. 变量表达式：X，我们仅支持单变量求导，表达式中为x
 * 3. 一元操作符表达式：Unary，是一元操作符，如sin, cos, ln
 * 4. 二元操作符表达式：Binary，是二元操作符，如+，-，*，/, ^
 * 而每一种表达式需要实现如下四种接口：
 * 1. hasVariable()，判断表达式中是否有变量，如果有返回true，否则返回false
 * 2. toStringRaw()，将表达式转换为字符串形式
 * 3.
 * evaluate()，计算表达式的值，若表达式中的变量还没有赋值，则抛出异常；若表达式中的变量已经赋值，则返回表达式的值
 * 4. getDerivative()，计算表达式的导数，返回一个表达式对象
 */

class Expression {
   public:
    virtual std::string toString() const;
    virtual bool alwaysZero() const;

    virtual bool hasVariable() const = 0;
    virtual double evaluate() const = 0;
    virtual double evaluate(double x) const = 0;
    virtual Expression* getDerivative() const = 0;
    virtual ~Expression() = default;
    protected:
    virtual std::string toStringRaw() const = 0;
};

class Constant : public Expression {
   public:
    explicit Constant(double value) : value(value) {}
    bool hasVariable() const final { return false; }
    std::string toStringRaw() const final { return std::to_string(value); }
    double evaluate() const final { return value; }
    double evaluate(double x) const final{ return value; }
    Expression* getDerivative() const final{ return new Constant(0); }

   private:
    double value;
};

class X : public Expression {
   public:
    X() = default;
    bool hasVariable() const final{ return true; }
    std::string toStringRaw() const final { return "x"; }
    double evaluate() const final { throw std::runtime_error("x is not set"); }
    double evaluate(double x) const final { return x; }
    Expression* getDerivative() const final { return new Constant(1); }
};

Expression* constant(double e);
Expression* variable();
#endif  // EXPRESSION_H
