//
// Created by 王少文 on 2022/1/17.
//
#include "Expression.h"


std::string Expression::toString() const {
    if(this->hasVariable()){
        return toStringRaw();
    }else{
        return std::to_string(this->evaluate());
    }
}

bool Expression::alwaysZero() const {
    return !this->hasVariable() && this->evaluate() == 0;
}

Expression* constant(double e){
    return new Constant(e);
}
Expression* variable(){
    return new X();
}