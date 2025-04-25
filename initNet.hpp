
#include <iostream>

#pragma once

using namespace std;



// ��������� 
const int IMAGE_SIZE = 784; // 28x28
const int HIDDEN_SIZE = 128; // 128 �������� � ������� ����
const int OUTPUT_SIZE = 10; // 10 �������� �������� ���� (0-9)


// ��������� ��������� ����
struct NeuralNetwork {
    double* input_layer; //������� ���� 784
	double* hidden_layer; //������� ���� 128
	double* output_layer; //�������� ���� 10

	double** weights_ih; //���� � �������� �� ������� ����
	double** weights_ho; //���� � �������� �� �������� ����

	double* bias_h; //�������� � �������� �� ������� ����
	double* bias_o; //�������� � �������� �� �������� ����
};


// ������������� ����
void init_network(NeuralNetwork* net) {
    
	//�������� ������ ��� ��������, �������� � ��������� �����
    net->input_layer = new double[IMAGE_SIZE];
    net->hidden_layer = new double[HIDDEN_SIZE];
    net->output_layer = new double[OUTPUT_SIZE];

    //�������� ������ ��� ����� � �������� �� ������� ���� � ��������� ���������� �� -1 �� 1
    net->weights_ih = new double* [IMAGE_SIZE];

    for (int i = 0; i < IMAGE_SIZE; i++) {
        net->weights_ih[i] = new double[HIDDEN_SIZE];

        for (int j = 0; j < HIDDEN_SIZE; j++) {
            net->weights_ih[i][j] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        }
    }

    //�������� ������ ��� ����� � �������� �� �������� ���� � ��������� ���������� �� -1 �� 1
    net->weights_ho = new double* [HIDDEN_SIZE];

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        net->weights_ho[i] = new double[OUTPUT_SIZE];

        for (int j = 0; j < OUTPUT_SIZE; j++) {
            net->weights_ho[i][j] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        }
    }

    //�������� ������ ��� �������� � �������� �� �������� ���� � ��������� ���������� �� -1 �� 1
    net->bias_h = new double[HIDDEN_SIZE];
    net->bias_o = new double[OUTPUT_SIZE];

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        net->bias_h[i] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
    }

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        net->bias_o[i] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
    }
}



// ������������ ������
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