#include "initNet.hpp"
#include "MnistPars.hpp"
#include "Propagetion.hpp"

#include <iostream>

#pragma once

using namespace std;


// Тестирование одного примера
int predict(NeuralNetwork* net, MNISTData* data, int index) {
    for (int i = 0; i < IMAGE_SIZE; i++) {
        net->input_layer[i] = ((unsigned char)data->images[index][i] / 255.0) * 0.99 + 0.01;
    }

    feedforward(net);

    int predicted = 0;
    double max_output = net->output_layer[0];
    for (int o = 1; o < OUTPUT_SIZE; o++) {
        if (net->output_layer[o] > max_output) {
            max_output = net->output_layer[o];
            predicted = o;
        }
    }

    return predicted;
}