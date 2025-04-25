#include <fstream>
#include <iostream>

#include "initNet.hpp"

using namespace std;


const std::string WEIGHTS_FILE = "mnist_weights.dat";

// Сохранение весов в файл
void save_weights(NeuralNetwork* net) {
    std::ofstream file(WEIGHTS_FILE, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Не удается открыть файл весов для записи!" << std::endl;
        return;
    }

    // Сохраняем веса input->hidden
    for (int i = 0; i < IMAGE_SIZE; i++) {
        file.write((char*)net->weights_ih[i], HIDDEN_SIZE * sizeof(double));
    }

    // Сохраняем веса hidden->output
    for (int h = 0; h < HIDDEN_SIZE; h++) {
        file.write((char*)net->weights_ho[h], OUTPUT_SIZE * sizeof(double));
    }

    // Сохраняем смещения
    file.write((char*)net->bias_h, HIDDEN_SIZE * sizeof(double));
    file.write((char*)net->bias_o, OUTPUT_SIZE * sizeof(double));

    file.close();
    std::cout << "Веса сохранены в " << WEIGHTS_FILE << std::endl;
}

// Загрузка весов из файла
bool load_weights(NeuralNetwork* net) {
    std::ifstream file(WEIGHTS_FILE, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Загружаем веса input->hidden
    for (int i = 0; i < IMAGE_SIZE; i++) {
        file.read((char*)net->weights_ih[i], HIDDEN_SIZE * sizeof(double));
    }

    // Загружаем веса hidden->output
    for (int h = 0; h < HIDDEN_SIZE; h++) {
        file.read((char*)net->weights_ho[h], OUTPUT_SIZE * sizeof(double));
    }

    // Загружаем смещения
    file.read((char*)net->bias_h, HIDDEN_SIZE * sizeof(double));
    file.read((char*)net->bias_o, OUTPUT_SIZE * sizeof(double));

    file.close();
    std::cout << "Веса загружены из " << WEIGHTS_FILE << std::endl;
    return true;
}
