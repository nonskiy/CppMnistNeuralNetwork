#include "initNet.hpp"
#include "mathAlgorithm.hpp"

#include <iostream>

#pragma once

using namespace std;


// Прямое распространение
void feedforward(NeuralNetwork* net) {
    
    // Входной - Скрытый
    for (int h = 0; h < HIDDEN_SIZE; h++) {
        double sum = net->bias_h[h];
        for (int i = 0; i < IMAGE_SIZE; i++) {
            sum += net->input_layer[i] * net->weights_ih[i][h];
        }
        net->hidden_layer[h] = sigmoid(sum);
    }

    // Скрытый - Выходной
    for (int o = 0; o < OUTPUT_SIZE; o++) {
        double sum = net->bias_o[o];
        for (int h = 0; h < HIDDEN_SIZE; h++) {
            sum += net->hidden_layer[h] * net->weights_ho[h][o];
        }
        net->output_layer[o] = sigmoid(sum);
    }
}

// Обратное распространение
void backpropagate(NeuralNetwork* net, int target, double learning_rate = 0.01) {
	
    // Ошибки выходного слоя
    double* output_errors = new double[OUTPUT_SIZE];
    for (int o = 0; o < OUTPUT_SIZE; o++) {
        double target_val = (o == target) ? 0.99 : 0.01;
        output_errors[o] = target_val - net->output_layer[o];
    }

	// Ошибки скрытого слоя
    double* hidden_errors = new double[HIDDEN_SIZE];
    for (int h = 0; h < HIDDEN_SIZE; h++) {
        hidden_errors[h] = 0.0;
        for (int o = 0; o < OUTPUT_SIZE; o++) {
            hidden_errors[h] += output_errors[o] * net->weights_ho[h][o];
        }
    }

	// Обновление весов Скрытого - Выходного слоя(Градиентный спуск)
    for (int h = 0; h < HIDDEN_SIZE; h++) {
        for (int o = 0; o < OUTPUT_SIZE; o++) {
            double delta = output_errors[o] * sigmoid_derivative(net->output_layer[o]);
            net->weights_ho[h][o] += net->hidden_layer[h] * delta * learning_rate;
        }
    }
    
	// Обновление весов Входного - Скрытого слоя(Градиентный спуск)
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int h = 0; h < HIDDEN_SIZE; h++) {
            double delta = hidden_errors[h] * sigmoid_derivative(net->hidden_layer[h]);
            net->weights_ih[i][h] += net->input_layer[i] * delta * learning_rate;
        }
    }

	// Обновление смещений(Градиентный спуск)
    for (int o = 0; o < OUTPUT_SIZE; o++) {
        double delta = output_errors[o] * sigmoid_derivative(net->output_layer[o]);
        net->bias_o[o] += delta * learning_rate;
    }

	// Обновление смещений(Градиентный спуск)
    for (int h = 0; h < HIDDEN_SIZE; h++) {
        double delta = hidden_errors[h] * sigmoid_derivative(net->hidden_layer[h]);
        net->bias_h[h] += delta * learning_rate;
    }

	// Освобождение памяти
    delete[] output_errors;
    delete[] hidden_errors;
}