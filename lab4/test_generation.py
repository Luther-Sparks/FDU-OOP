from glob import glob
from pickle import FALSE, TRUE
from site import execsitecustomize
from itsdangerous import exc
from sympy import *
import random

POLYNOMIAL = TRUE

def term():
    # 四种情况
    # 3/6的概率是x
    # 1/6的概率是1
    # 1/6的概率是0
    # 1/6的概率是[-10,10]的任意常数
    c = random.choice(range(6))
    if c <= 2:
        return Symbol('x')
    elif c == 3:
        return 1
    elif c == 4:
        return 0
    else:
        return int(random.uniform(-10, 10)*1000)/1000


def expr():
    # 三种情况
    # 1/3的概率是binary_expr
    # 1/3的概率是unary_expr
    # 1/3的概率是term
    c = random.choice(range(3))
    if c == 0:
        return binary_expr(expr(), expr())
    elif c == 1:
        return unary_expr(expr())
    else:
        return term()


def binary_expr(left, right):
    # 四种情况
    # 1/4的概率是left + right
    # 1/4的概率是left - right
    # 1/4的概率是left * right
    # 1/4的概率是left / right
    c = random.choice(range(4))
    if c == 0:
        return left + right
    elif c == 1:
        return left - right
    elif c == 2:
        return left * right
    else:
        return left / right


def unary_expr(expr):
    # 三种情况
    # 1/3的概率是-expr
    # 1/3的概率是sin(expr)
    # 1/3的概率是cos(expr
    if POLYNOMIAL:
        return -expr

    c = random.choice(range(3))
    if c == 0:
        return -expr
    elif c == 1:
        return sin(expr)
    else:
        return cos(expr)

def form_test(test_version:str , expr_str:str, test_val:float, expr_result: float, diff_result: float)->str:
    return f'TEST("{test_version}" ,"{expr_str}", {test_val}, {expr_result}, {diff_result});'

def test_once(test_version: str):
    while True:
        test_vals = [-1,0,1,0.618,random.random(),random.random()]
        try:
            e = expr()
        except Exception:
            continue
        # 长度必须在30到100之间
        if len(str(e)) < 30 or len(str(e)) > 100:
            continue
        # 限制不允许有无穷的情况
        if e.has(oo, -oo, zoo, nan):
            continue
        for test_index,test_val in enumerate(test_vals):
            try:
                s = form_test(
                    test_version = test_version+f"_{test_index}",
                    expr_str = str(e),
                    test_val = test_val,
                    expr_result = e.evalf(subs = {"x": test_val}),
                    diff_result = e.diff().evalf(subs = {"x": test_val})
                )  
                print(s)
            except ZeroDivisionError:
                pass
        return



def generate_test(num: int):
    for i in range(num):
        test_once("polynomial_"+str(i))
    global POLYNOMIAL
    POLYNOMIAL = FALSE
    for i in range(num):
        test_once("complex_"+str(i))

if __name__ == "__main__":
    generate_test(10)
