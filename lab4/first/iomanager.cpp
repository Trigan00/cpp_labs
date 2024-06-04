#include <iostream>
#include <fstream>
#include <cstring>

void readFromConsole(char*& buffer, int& size) {
    int capacity = 0;
    int length = 0;
    buffer = new char[capacity];

    char ch;
    std::cout << "Введите строку: "; //TODO не понимает русское
    while (std::cin.get(ch) && ch != '\n') {
        buffer[length++] = ch;
        if (length == capacity) {
            capacity *= 2;
            char* temp = new char[capacity];
            std::copy(buffer, buffer + length, temp);
            delete[] buffer;
            buffer = temp;
        }
    }
    buffer[length] = '\0';
    size = length;
}

int readFromFile(const char* filename, char*& buffer, int& fileSize) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cout << "Ошибка открытия файла.\n";
        return 1;
    }

    // inFile.seekg(0, std::ios::end);
    // fileSize = inFile.tellg();
    // inFile.seekg(0, std::ios::beg);
    const int MAX_LENGTH = 1000;
    bool isEmpty {true}; 
    buffer = new char[MAX_LENGTH];
    bool isLine {false};
    

    while (inFile.getline(buffer, MAX_LENGTH)) {
        if (buffer[0] != '\0') {
            if (isLine){
                std::cout << "Ошибка: Введите одну строку" << std::endl;
                exit(1);
            }
            isEmpty = false;
            fileSize = strlen(buffer);
            isLine = true;
        }
    }


    // inFile.read(buffer, fileSize);

    // if (!inFile) {
    //     std::cout << "Ошибка чтения файла.\n";
    //     return 1;
    // }

    inFile.close();
    if (isEmpty) {
        std::cout << "Ошибка: Файл не может быть пустым." << std::endl;
        exit(1);
    }

    return 0;
}

void writeToConsole(const char* buffer, int fileSize) {
    std::cout << "Результат выполнения программы:\n";
    for (int i = 0; i < fileSize; ++i) {
        std::cout << buffer[i];
    }
    std::cout << std::endl;
}

int writeToFile(const char* filename, const char* buffer, int fileSize) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "Ошибка открытия файла.\n";
        return 1;
    }

    outFile.write(buffer, fileSize);

    if (!outFile) {
        std::cout << "Ошибка записи в файл.\n";
        return 1;
    }

    outFile.close();

    return 0;
}


// int readFromFile(const char* filename, char*& buffer, int& fileSize) {
//     std::ifstream inFile(filename);

//     if (!inFile.is_open()) {
//         std::cout << "Ошибка открытия файла.\n";
//         return 1;
//     }

//     const int MAX_LENGTH = 1000;
//     bool isEmpty {true}; 
//     delete[] buffer;
//     buffer = new char[MAX_LENGTH];
//     bool isLine {false};

//     char ch;
//     int index = 0;
//     while (inFile.get(ch)) {
//         // Проверяем, не является ли символ символом новой строки или конца файла
//         if (ch != '\n' && ch != EOF) {
//             buffer[index++] = ch;
//         } else {
//             // Устанавливаем нуль-терминатор в конец строки
//             buffer[index] = '\0';
            
//             // Проверяем, не является ли строка пустой
//             if (index != 0) {
//                 if (isLine){
//                     std::cout << "Ошибка: Введите одну строку" << std::endl;
//                     exit(1);
//                 }
//                 isEmpty = false;
//                 fileSize = strlen(buffer);
//                 isLine = true;
//             }
//             index = 0; // Сбрасываем индекс для следующей строки
//         }
//     }

//     inFile.close();
//     if (isEmpty) {
//         std::cout << "Ошибка: Файл не может быть пустым." << std::endl;
//         exit(1);
//     }

//     return 0;
// }
