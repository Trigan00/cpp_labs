#include <iostream>

void averageColumns(int n, double** matrix, double* resultarr) {
    //double averages[9] = {0}; // Инициализируем массив средних значений нулями

    for (int col = 0; col < 9; ++col) {
        double sum = 0.0;
        for (int row = 0; row < n; ++row) {
            sum += matrix[row][col];
        }
        resultarr[col] = sum / n;
    }

}

double task(const int n, double* resultarr) {
    double matrix[n][n];

    std::cout << "Enter the elements of the matrix:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) { // n was 9
            std::cin >> matrix[i][j];
        }
    }

    averageColumns(n, matrix, resultarr);

    return 0;
}
