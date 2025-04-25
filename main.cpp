#include <iostream>
#include <fstream>

#include "initNet.hpp"
#include "mathAlgorithm.hpp"
#include "MnistPars.hpp"
#include "Propagetion.hpp"
#include "Weights.hpp"
#include "Train.hpp"
#include "Predict.hpp"

#pragma once


using namespace std;

// ���������
const int TRAIN_SAMPLES = 60000;
const int TEST_SAMPLES = 10000;


int main() {
    srand(time(NULL));
    setlocale(0, "");

    NeuralNetwork net;
    init_network(&net);

    MNISTData train_data, test_data;

    load_mnist_images("mnist\\train-images.idx3-ubyte", &train_data);
    load_mnist_labels("mnist\\train-labels.idx1-ubyte", &train_data);

    load_mnist_images("mnist\\t10k-images.idx3-ubyte", &test_data);
    load_mnist_labels("mnist\\t10k-labels.idx1-ubyte", &test_data);

    // �������� ��������� ����
    bool weights_loaded = load_weights(&net);

   


    if (!weights_loaded) {
        cout << "**************************************************" << endl;
        cout << "*************�������� ���������*******************" << endl;
        cout << "**************************************************" << endl;
        // ���� ����� ��� - �������
        cout << "�� ������ ���� � ������. �������� ��������� � ������..." << endl;
        train(&net, &train_data, 5);
        save_weights(&net);
    }
    else {
        cout << "**************************************************" << endl;
        cout << "*************���������� ���������*****************" << endl;
        cout << "**************************************************" << endl;
        
    }

    // ������������� �����
    cout << "\n������� ����� ��������� ������� (0-9999) ��� -1 ��� ������:" << endl;

    while (true) {
        int index;
        cout << "> ";
        cin >> index;

        if (index < -1 || index >= TEST_SAMPLES) {
            cin.clear();
            cout << "������������ ����. ������� ����� �� 0 �� 9999 ��� -1 ��� ������." << endl;
            continue;
        }

        if (index == -1) break;

        // �������� ASCII-��� �����
        cout << "\n�������� ������ #" << index << endl;
        cout << "��������� �����: " << (int)(unsigned char)test_data.labels[index] << endl;
        display_digit(test_data.images[index]);

        // ���������� �����
        int predicted = predict(&net, &test_data, index);
        cout << "��������� ����������: " << predicted << endl << endl;
    }

    free_network(&net);
    free_mnist(&train_data);
    free_mnist(&test_data);

    return 0;
}