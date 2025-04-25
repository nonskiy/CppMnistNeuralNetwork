#include <iostream>
#include <fstream>
#include <string>

#pragma once

using namespace std;




// Структуры данных
struct MNISTData {
    string* images;
    string labels;
    int count;
};


// преобразование int в обратный порядок байтов
int reverse_int(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

// Загрузка MNIST
void load_mnist_images(const string filename, MNISTData* data) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Не открывается файл с изображением!" << endl;
        return;
    }

    int magic_number = 0;
    int number_of_images = 0;
    int rows = 0;
    int cols = 0;

    file.read((char*)&magic_number, sizeof(magic_number));
    magic_number = reverse_int(magic_number);

    file.read((char*)&number_of_images, sizeof(number_of_images));
    number_of_images = reverse_int(number_of_images);

    file.read((char*)&rows, sizeof(rows));
    rows = reverse_int(rows);

    file.read((char*)&cols, sizeof(cols));
    cols = reverse_int(cols);

    data->count = number_of_images;
    data->images = new string[number_of_images];

    for (int i = 0; i < number_of_images; i++) {
        char* buffer = new char[IMAGE_SIZE];
        file.read(buffer, IMAGE_SIZE);
        data->images[i].assign(buffer, IMAGE_SIZE);
        delete[] buffer;
    }

    file.close();
}

// Загрузка меток MNIST
void load_mnist_labels(const string filename, MNISTData* data) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Нельзя открыть файл с метками!" << endl;
        exit(1);
    }

    int magic_number = 0;
    int number_of_items = 0;

    file.read((char*)&magic_number, sizeof(magic_number)); //Считывает с файла и записывает в переменную размером 4 байта(int)
    magic_number = reverse_int(magic_number);

    file.read((char*)&number_of_items, sizeof(number_of_items));
    number_of_items = reverse_int(number_of_items);

    char* buffer = new char[number_of_items];
    file.read(buffer, number_of_items);
    data->labels.assign(buffer, number_of_items); //Заполняем массив метками (байтами) из файла
    delete[] buffer;

    file.close();
}

// Освобождение памяти MNIST
void free_mnist(MNISTData* data) {
    delete[] data->images;
}

// Функция для отображения ASCII-арта цифры
void display_digit(const string& image) {
    for (int y = 0; y < 28; y++) {
        for (int x = 0; x < 28; x++) {
            unsigned char pixel = image[y * 28 + x];
            char c = pixel > 128 ? '#' : pixel > 64 ? '+' : pixel > 32 ? '.' : ' ';
            cout << c;
        }
        cout << endl;
    }
}