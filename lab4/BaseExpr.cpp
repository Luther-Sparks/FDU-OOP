//
// Created by 王少文 on 2022/1/17.
//
#include "BaseExpr.h"


std::string BaseExpr::toString() const {
    if(this->hasVariable()){
        return toStringRaw();
    }else{
        return Constant(this->evaluate()).toStringRaw();
    }
}

bool BaseExpr::alwaysZero() const {
    return !this->hasVariable() && this->evaluate() == 0;
}