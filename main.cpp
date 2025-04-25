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

// Константы
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

    // Пытаемся загрузить веса
    bool weights_loaded = load_weights(&net);

   


    if (!weights_loaded) {
        cout << "**************************************************" << endl;
        cout << "*************ОБУЧЕНИЕ НЕЙРОСЕТИ*******************" << endl;
        cout << "**************************************************" << endl;
        // Если весов нет - обучаем
        cout << "Не найден файл с весами. Обучение нейросети с начала..." << endl;
        train(&net, &train_data, 5);
        save_weights(&net);
    }
    else {
        cout << "**************************************************" << endl;
        cout << "*************ТЕСТИРОВКА НЕЙРОСЕТИ*****************" << endl;
        cout << "**************************************************" << endl;
        
    }

    // Интерактивный режим
    cout << "\nВведите номер тестового примера (0-9999) или -1 для выхода:" << endl;

    while (true) {
        int index;
        cout << "> ";
        cin >> index;

        if (index < -1 || index >= TEST_SAMPLES) {
            cin.clear();
            cout << "Некорректный ввод. Введите число от 0 до 9999 или -1 для выхода." << endl;
            continue;
        }

        if (index == -1) break;

        // Показать ASCII-арт цифры
        cout << "\nТестовый пример #" << index << endl;
        cout << "Ожидаемая цифра: " << (int)(unsigned char)test_data.labels[index] << endl;
        display_digit(test_data.images[index]);

        // Распознать цифру
        int predicted = predict(&net, &test_data, index);
        cout << "Нейросеть распознала: " << predicted << endl << endl;
    }

    free_network(&net);
    free_mnist(&train_data);
    free_mnist(&test_data);

    return 0;
}