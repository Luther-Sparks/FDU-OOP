#include "BaseExpr.h"

bool BaseExpr::alwaysZero() const {
    return !this->hasVariable() && this->evaluate() == 0;
}