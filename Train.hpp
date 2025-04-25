#include <iostream>


#include "initNet.hpp"
#include "MnistPars.hpp"
#include "Propagetion.hpp"

using namespace std;


// ќбучение
void train(NeuralNetwork* net, MNISTData* data, int epochs) {
    for (int e = 0; e < epochs; e++) {
        double error = 0.0;
        for (int s = 0; s < data->count; s++) {
            for (int i = 0; i < IMAGE_SIZE; i++) {
                net->input_layer[i] = ((unsigned char)data->images[s][i] / 255.0) * 0.99 + 0.01;
            }

            feedforward(net);
            backpropagate(net, (unsigned char)data->labels[s]);

            int predicted = 0;
            double max_output = net->output_layer[0];
            for (int o = 1; o < OUTPUT_SIZE; o++) {
                if (net->output_layer[o] > max_output) {
                    max_output = net->output_layer[o];
                    predicted = o;
                }
            }
            if (predicted != (unsigned char)data->labels[s]) error += 1.0; // если не совпадают метки то ошибка
        }
        error /= data->count;
        std::cout << "Ёпоха " << e + 1 << ", ќшибка: " << error * 100 <<"%" << std::endl;
    }
}