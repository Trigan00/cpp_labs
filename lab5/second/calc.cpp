#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "valid.h"


using namespace std;

// Функция для поиска номеров строк, в которых все элементы - нули
vector<int> findZeroRows(const vector<vector<int>>& matrix) {
    vector<int> zeroRows;
    for (int i = 0; i < matrix.size(); ++i) {
        bool allZero = true;
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != 0) {
                allZero = false;
                break;
            }
        }
        if (allZero) {
            zeroRows.push_back(i);
        }
    }
    return zeroRows;
}

// Функция для поиска номеров строк, в которых все элементы одинаковы
vector<int> findSameElementRows(const vector<vector<int>>& matrix) {
    vector<int> sameElementRows;
    for (int i = 0; i < matrix.size(); ++i) {
        bool sameElement = true;
        for (int j = 1; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != matrix[i][0]) {
                sameElement = false;
                break;
            }
        }
        if (sameElement) {
            sameElementRows.push_back(i);
        }
    }
    return sameElementRows;
}

// Функция для поиска номеров строк, в которых все элементы четные
vector<int> findEvenRows(const vector<vector<int>>& matrix) {
    vector<int> evenRows;
    for (int i = 0; i < matrix.size(); ++i) {
        bool allEven = true;
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] % 2 != 0) {
                allEven = false;
                break;
            }
        }
        if (allEven) {
            evenRows.push_back(i);
        }
    }
    return evenRows;
}

// Функция для проверки, является ли последовательность монотонной
bool isMonotonic(const vector<int>& sequence) {
    bool increasing = true;
    bool decreasing = true;
    for (int i = 1; i < sequence.size(); ++i) {
        if (sequence[i] > sequence[i - 1]) {
            decreasing = false;
        } else if (sequence[i] < sequence[i - 1]) {
            increasing = false;
        }
    }
    return increasing || decreasing;
}

// Функция для поиска номеров строк, в которых элементы образуют монотонную последовательность
vector<int> findMonotonicRows(const vector<vector<int>>& matrix) {
    vector<int> monotonicRows;
    for (int i = 0; i < matrix.size(); ++i) {
        if (isMonotonic(matrix[i])) {
            monotonicRows.push_back(i);
        }
    }
    return monotonicRows;
}

void readMatrixFromFile(const char* filename, int& numRows, int& numCols) {
    std::string filePath;
    std::cout << "Укажите файл для ввода исходных данных для работы программы (нажмите Enter для использования " << filename << "): ";
    getline(std::cin, filePath);

    if (filePath.empty()) {
        filePath = filename;
    }
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Ошибка: Файл не найден или не удалось открыть файл." << std::endl;
        exit(1);
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
            if (!isValidInteger(token)) {
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

int output(const char* outputFile, vector<vector<int>> matrix){
    // Поиск номеров строк
    vector<int> zeroRows = findZeroRows(matrix);
    vector<int> sameElementRows = findSameElementRows(matrix);
    vector<int> evenRows = findEvenRows(matrix);
    vector<int> monotonicRows = findMonotonicRows(matrix);


    while (true)
    {
        int outputDestination = getN("Куда вы хотите записать информацию? Консоль - 1, файл - 2: ");
        if (outputDestination == 2) {
            std::string filePath;
            std::cout << "Укажите файл для вывода данных (нажмите Enter для использования " << outputFile << "): ";
            getline(std::cin, filePath);

            if (filePath.empty()) {
                filePath = outputFile;
            }
            std::ofstream file(filePath);

            if (!file.is_open()) {
                std::cerr << "Ошибка: Файл не найден или не удалось открыть файл." << std::endl;
                continue;
            }
            file << "Строки со всеми нулевыми элементами:";
            for (int row : zeroRows) file << " " << row;
            file << endl;

            file << "Строки со всеми одинаковыми элементами:";
            for (int row : sameElementRows) file << " " << row;
            file << endl;

            file << "Строки со всеми четными элементами:";
            for (int row : evenRows) file << " " << row;
            file << endl;

            file << "Строки с монотонной последовательностью элементов:";
            for (int row : monotonicRows) file << " " << row;
            file << endl;
            
            file.close();
            std::cout << "Информация записана в файл" << std::endl;
            break;
        } else if (outputDestination == 1) {            
            cout << "Строки со всеми нулевыми элементами:";
            for (int row : zeroRows) cout << " " << row;
            cout << endl;

            cout << "Строки со всеми одинаковыми элементами:";
            for (int row : sameElementRows) cout << " " << row;
            cout << endl;

            cout << "Строки со всеми четными элементами:";
            for (int row : evenRows) cout << " " << row;
            cout << endl;

            cout << "Строки с монотонной последовательностью элементов:";
            for (int row : monotonicRows) cout << " " << row;
            cout << endl;
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

    if (numRows != numCols){
        std::cerr << "Ошибка: Необходимо ввести квадратную матрицу" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numRows));


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

    // double* means = calculateColumnMeans(matrix, numRows, numCols);
    
    output(outputFile, matrix);
    

    return 0;
}

int RWConsole(const char* outputFile){
    int n = getN("Введите n: ");

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    std::cout << "Введите элементы матрицы:" << std::endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            const int bufferSize = 256;
            char input[bufferSize];
            
            while (true) {
                std::cout << "Элемент (" << i << "," << j << "): ";
                std::cin.getline(input, bufferSize);
                if (!isValidInteger(input)) {
                    std::cout << "Ошибка: \"" << input << "\" не является допустимым числом." << std::endl;
                    continue;
                }else{
                    matrix[i][j] = std::stoi(input);
                    break;
                }
            }
        }
    }

    // Вывод матрицы для проверки
    std::cout << "Матрица:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // double* means = calculateColumnMeans(matrix, numRows, numCols);
    
    output(outputFile, matrix);

    return 0;
}
