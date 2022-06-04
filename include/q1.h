#ifndef Q1_H
#define Q1_H

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace q1 {

template <typename T, typename Func>
// define derviate function for calculate gradient_descent -> f'(x) = f(x+h)-f(x-h)/2*h and h goes to 0
double moshtagh(T point, Func func)
{
    double eps { 0.001 };
    double moshataghat { (func(point + eps) - func(point - eps)) / (2.0 * eps) };
    return moshataghat;
}

template <typename T, typename Func>
double gradient_descent(T ivalue, double step, Func func = Func {})
{
    double learning_rate = { step };
    T iv { ivalue };
    double taghirat { learning_rate * moshtagh(iv, func) };
    while (std::abs(taghirat) >= 0.000000001) {
        taghirat = learning_rate * moshtagh(iv, func);
        iv = iv - taghirat;
    }
    return iv;
}
}

#endif