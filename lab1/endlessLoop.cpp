#include <iostream>
#include <math.h>

size_t update_t(size_t t) {
    size_t f_t = exp(t) + (t + 1);
    size_t df_t = exp(t) + 1;
    return t - f_t/df_t;
    
}

size_t fibonacci(size_t n) {
    if (n <= 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char const *argv[]) {
    size_t res = fibonacci(0);
    for (size_t t = 10; t >= 0; t = update_t(t)) {
        res = fibonacci(res);
    }
    std::cout << res << std::endl;
    return 0; 
}
