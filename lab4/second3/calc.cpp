#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>
#include "valid.h"


double* calculateColumnMeans(double** matrix, int rows, int cols) {
    double* means = new double[cols];
    for (int j = 0; j < cols; ++j) {
        double sum = 0.0;
        for (int i = 0; i < rows; ++i) {
            sum += matrix[i][j];
        }
        means[j] = sum / rows;
    }
    return means;
}

void readMatrixFromFile(const char* filename, int& numRows, int& numCols) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Невозможно открыть файл: " << filename << std::endl;
        return;
    }

    // Переменная для подсчета строк и столбцов
    numRows = 0;
    numCols = -1; // Начинаем с -1, чтобы первую строку считать в столбцах

    // char buffer[bufferSize];
    char* buffer = new char[bufferSize];
    bool isChar {false};

    while (file.getline(buffer, bufferSize)) {
        int colsInRow {0};
        
        std::istringstream iss(buffer);
        char token[bufferSize];
        while (iss >> token) {
            isChar = true;
            ++colsInRow;
            if (!isNumber(token)) {
                std::cout << "Ошибка: \"" << token << "\" не является допустимым числом." << std::endl;
                exit(1);
            }
        }
        
        if (colsInRow == 0) // Если строка не содержит чисел, считаем это пустой строкой
            continue;

        if (numCols == -1) // Если это первая строка, устанавливаем количество столбцов
            numCols = colsInRow;
        else if (colsInRow != numCols){ // Проверяем, равны ли количество элементов в строках
            std::cout << "Ошибка: Неравномерное количество элементов в строках матрицы." << std::endl;
            exit(1);
        }

        ++numRows;
    }

    file.close();
    delete buffer;

    if (!isChar){
        std::cout << "Ошибка: Файл не может быть пустым." << std::endl;
        exit(1);
    }
}

int output(const char* outputFile, int numCols, double* means){
    while (true)
    {
        int outputDestination = getN("Куда вы хотите записать информацию? Консоль - 1, файл - 2: ");
        if (outputDestination == 2) {
            std::ofstream outFile(outputFile);

            if (!outFile.is_open()) {
                std::cout << "Ошибка открытия файла.\n";
                return 1;
            }

            outFile << "Средние значения каждого столбца: " << std::endl;
            for (int j = 0; j < numCols; ++j) {
                outFile << "Колонка " << j << ": " << means[j] << std::endl;
            }
            
            outFile << "\nСреднее значение каждого столбца, имеющего четный номер: " << std::endl;
            for (int j = 0; j < numCols; ++j) {
                if (j % 2 == 0) outFile << "Колонка " << j << ": " << means[j] << std::endl;
            }
            outFile.close();
            std::cout << "Информация записана в файл" << std::endl;
            break;
        } else if (outputDestination == 1) {
            std::cout << "Средние значения каждого столбца: " << std::endl;
            for (int j = 0; j < numCols; ++j) {
                std::cout << "Колонка " << j << ": " << means[j] << std::endl;
            }
            std::cout << "Среднее значение каждого столбца, имеющего четный номер: " << std::endl;
            for (int j = 0; j < numCols; ++j) {
                if (j % 2 == 0) std::cout << "Колонка " << j << ": " << means[j] << std::endl;
            }

            break;
        } else {
            std::cout << "Неверное место назначения. Введите 1 или 2.\n";
            continue;
        }
    }
    return 0;
}

int RWFile(const char* inputFile, const char* outputFile) {

    int numRows, numCols;
    readMatrixFromFile(inputFile, numRows, numCols);

    double** matrix = new double*[numRows];
    for (int i = 0; i < numRows; ++i) {
        matrix[i] = new double[numCols];
    }

    std::ifstream in("matrix.txt");

    if (in.is_open()){    
        for (int i = 0; i < numRows; i++){
            for (int j = 0; j < numCols; j++)
                in >> matrix[i][j];
        }
    }else{
        std::cerr << "Невозможно открыть файл: " << inputFile << std::endl;
        return 1;
    }

    // Вывод матрицы для проверки
    std::cout << "Матрица:" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    double* means = calculateColumnMeans(matrix, numRows, numCols);
    
    output(outputFile, numCols, means);
    

    for (int i = 0; i < numRows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] means;

    return 0;
}

int RWConsole(const char* outputFile){
    int numRows = getN("Количесво строк: ");
    int numCols = getN("Количесво столбцов: ");

    double** matrix = new double*[numRows];
    for (int i = 0; i < numRows; ++i) {
        matrix[i] = new double[numCols];
    }

    std::cout << "Введите элементы матрицы:" << std::endl;
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            const int bufferSize = 256;
            char input[bufferSize];
            
            while (true) {
                std::cout << "Элемент (" << i << "," << j << "): ";
                std::cin.getline(input, bufferSize);
                if (!isNumber(input)) {
                    std::cout << "Ошибка: \"" << input << "\" не является допустимым числом." << std::endl;
                    continue;
                }else{
                    matrix[i][j] = std::stod(input);
                    break;
                }
            }
        }
    }

    // Вывод матрицы для проверки
    std::cout << "Матрица:" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    double* means = calculateColumnMeans(matrix, numRows, numCols);
    
    output(outputFile, numCols, means);

    for (int i = 0; i < numRows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] means;

    return 0;
}

void testChar () {
    // cout << buffer;
        // int i {0};
        // int j {0};
        // char* temp = new char[10];
        // while(true){
        //     if (buffer[i] == '\0'){
        //         break;
        //     }
        //     // cout << buffer[i];
        //     if(buffer[i] != ' ' ){
        //         temp[j] = buffer[i];
        //         j++;
        //     }else{
        //         if (!isNumber(temp)) {
        //             cout << "Ошибка: \"" << temp << "\" не является допустимым числом." << endl;
        //             exit(1);
        //         }else{
                    
        //             ++colsInRow;
        //             // j = 0;
        //             delete[] temp;
        //             temp = new char[10];
                    
        //         }
        //     }
        //     i++;
        // }
}