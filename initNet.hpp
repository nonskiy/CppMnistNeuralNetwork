
#include <iostream>

#pragma once

using namespace std;



// Константы 
const int IMAGE_SIZE = 784; // 28x28
const int HIDDEN_SIZE = 128; // 128 нейронов в скрытом слое
const int OUTPUT_SIZE = 10; // 10 нейронов выходной слой (0-9)


// структура нейронной сети
struct NeuralNetwork {
    double* input_layer; //входнйо слой 784
	double* hidden_layer; //скрытый слой 128
	double* output_layer; //выходной слой 10

	double** weights_ih; //веса с входного на скрытый слой
	double** weights_ho; //веса с скрытого на выходной слой

	double* bias_h; //смещения с входного на скрытый слой
	double* bias_o; //смещения с скрытого на выходной слой
};


// Инициализация сети
void init_network(NeuralNetwork* net) {
    
	//Выделяем память для входного, скрытого и выходного слоев
    net->input_layer = new double[IMAGE_SIZE];
    net->hidden_layer = new double[HIDDEN_SIZE];
    net->output_layer = new double[OUTPUT_SIZE];

    //Выделяем память для весов с входного на скрытый слой и заполняем значениями от -1 до 1
    net->weights_ih = new double* [IMAGE_SIZE];

    for (int i = 0; i < IMAGE_SIZE; i++) {
        net->weights_ih[i] = new double[HIDDEN_SIZE];

        for (int j = 0; j < HIDDEN_SIZE; j++) {
            net->weights_ih[i][j] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        }
    }

    //Выделяем память для весов с скрытого на выходной слой и заполняем значениями от -1 до 1
    net->weights_ho = new double* [HIDDEN_SIZE];

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        net->weights_ho[i] = new double[OUTPUT_SIZE];

        for (int j = 0; j < OUTPUT_SIZE; j++) {
            net->weights_ho[i][j] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        }
    }

    //Выделяем память для смещений с скрытого на выходной слой и заполняем значениями от -1 до 1
    net->bias_h = new double[HIDDEN_SIZE];
    net->bias_o = new double[OUTPUT_SIZE];

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        net->bias_h[i] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
    }

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        net->bias_o[i] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
    }
}



// Освобождение памяти
void free_network(NeuralNetwork* net) {
    delete[] net->input_layer;
    delete[] net->hidden_layer;
    delete[] net->output_layer;

    for (int i = 0; i < IMAGE_SIZE; i++) delete[] net->weights_ih[i];
    delete[] net->weights_ih;

    for (int i = 0; i < HIDDEN_SIZE; i++) delete[] net->weights_ho[i];
    delete[] net->weights_ho;

    delete[] net->bias_h;
    delete[] net->bias_o;
}