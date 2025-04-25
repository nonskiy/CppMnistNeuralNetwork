#include <iostream>

#pragma once

using namespace std;

// Функции активации
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Производная функции активации для обратного распространения
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}