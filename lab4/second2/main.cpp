#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>

using namespace std;


bool isNumber(const string &s) {
    bool hasDecimal = false;
    bool hasDigit = false;

    for (char c : s) {
        if (c == '-' && !hasDigit) continue; // минус может быть только в начале числа
        if (isdigit(c)) {
            hasDigit = true;
            continue;
        }
        if (c == '.' && !hasDecimal) {
            hasDecimal = true;
            continue;
        }
        return false;
    }
    return hasDigit;
}

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
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    // Переменная для подсчета строк и столбцов
    numRows = 0;
    numCols = -1; // Начинаем с -1, чтобы первую строку считать в столбцах

    // Флаги для отслеживания ошибок
    bool foundNonDigit = false;
    bool multipleSpaces = false;
    bool unevenCols = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) // Пропускаем пустые строки
            continue;

        std::istringstream iss(line);
        int colsInRow = 0;
        // char prevChar = ' '; // Инициализируем предыдущий символ пробелом, чтобы не сработало условие для первого символа

        // double num;
        std::string token;
        while (iss >> token) {
            ++colsInRow;
            if (!isNumber(token)) {
                cout << "Ошибка: \"" << token << "\" не является допустимым числом." << endl;
                exit(1);
            }

            // if (colsInRow > 1 && token == ""){ // Между элементами матрицы больше одного пробела
            //     multipleSpaces = true;
            //     std::cerr << "Error: Found multiple spaces between matrix elements." << std::endl;
            //     exit(1);
            // }
        }
        
        if (colsInRow == 0) // Если строка не содержит чисел, считаем это пустой строкой
            continue;

        if (numCols == -1) // Если это первая строка, устанавливаем количество столбцов
            numCols = colsInRow;
        else if (colsInRow != numCols){ // Проверяем, равны ли количество элементов в строках
            unevenCols = true;
            std::cerr << "Error: Uneven number of elements in matrix rows." << std::endl;
            exit(1);
        }

        ++numRows;
    }

    file.close();
}

int main() {

    const char* filename = "matrix.txt";
    int numRows, numCols;
    readMatrixFromFile(filename, numRows, numCols);
    std::cout << "Number of rows: " << numRows << std::endl;
    std::cout << "Number of columns: " << numCols << std::endl;

    // Dynamically allocate memory for the matrix
    double** matrix = new double*[numRows];
    for (int i = 0; i < numRows; ++i) {
        matrix[i] = new double[numCols];
    }

    ifstream in("matrix.txt");

    if (in.is_open()){    
        for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            in >> matrix[i][j];
    }else{
        std::cerr << "Unable to open file: " << filename << std::endl;
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

    return 0;




    // ifstream inputFile("matrix.txt");
    // if (!inputFile.is_open()) {
    //     cout << "Failed to open the file." << endl;
    //     return 1;
    // }

    // // skipEmptyLines(inputFile);

    // int rows = 0;
    // int cols = 0;
    // char ch;

    // // Counting rows and columns
    // while (inputFile.get(ch)) {
    //     if (ch == '\n') {
    //         ++rows;
    //         break;
    //     } else if (ch == ' ') {
    //         ++cols;
    //     } else if (!isdigit(ch) && ch != '-' && ch != '.') {
    //         cout << "Invalid character found in matrix." << endl;
    //         return 1;
    //     }
    // }
    // ++cols; // Increment to count the last element in the row

    
    // cout << "rows: " << rows << endl;
    // cout << "cols: " << cols << endl;

    // // Dynamically allocate memory for the matrix
    // double** matrix = new double*[rows];
    // for (int i = 0; i < rows; ++i) {
    //     matrix[i] = new double[cols];
    // }

    // // Rewind to the beginning of the file
    // inputFile.clear();
    // inputFile.seekg(0, ios::beg);
    // // skipEmptyLines(inputFile);

    // // Reading matrix from the file
    // for (int i = 0; i < rows; ++i) {
    //     for (int j = 0; j < cols; ++j) {
    //         inputFile >> matrix[i][j];
    //         if (!isNumber(to_string(matrix[i][j]).c_str())) {
    //             cout << "Invalid number format in matrix." << endl;
    //             return 1;
    //         }
    //     }
    //     if (inputFile.peek() != '\n') {
    //         cout << "Too many elements in a row." << endl;
    //         return 1;
    //     }
    //     inputFile.ignore(1, '\n'); // Ignore the newline character
    // }

    // // Check if the number of elements in each row is consistent
    // for (int i = 1; i < rows; ++i) {
    //     if (cols != cols) {
    //         cout << "Number of elements in rows is not consistent." << endl;
    //         return 1;
    //     }
    // }

    // // Calculate column means
    // double* means = calculateColumnMeans(matrix, rows, cols);

    // // Output column means
    // cout << "Column means:" << endl;
    // for (int j = 0; j < cols; ++j) {
    //     cout << "Column " << j + 1 << ": " << means[j] << endl;
    // }

    // // Clean up memory
    // for (int i = 0; i < rows; ++i) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;
    // delete[] means;

    // inputFile.close();
    // return 0;
}
