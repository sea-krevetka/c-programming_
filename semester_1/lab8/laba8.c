#include <stdio.h>

#define MAX_SIZE 100  


double determinant2x2(double matrix[2][2]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}


double determinant3x3(double matrix[3][3]) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}


double determinant(double matrix[MAX_SIZE][MAX_SIZE], int n) {
    if (n == 1) {
        return matrix[0][0]; 
    }

    double det = 0;
    

    for (int col = 0; col < n; col++) {
        double minor[MAX_SIZE][MAX_SIZE];

        // Заполнение минора для элемента в первом ряду и колонке col
        for (int i = 1; i < n; i++) {
            for (int j = 0, minor_col = 0; j < n; j++) {
                if (j == col) continue;  // Пропускаем текущую колонку
                minor[i - 1][minor_col] = matrix[i][j];
                minor_col++;
            }
        }

        double sign = (col % 2 == 0) ? 1 : -1;

        det += sign * matrix[0][col] * determinant(minor, n - 1);
    }

    return det;
}

void printMatrix(double matrix[MAX_SIZE][MAX_SIZE], int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N;
    printf("Введите размерность матрицы: ");
    scanf("%d", &N);

    if (N < 1 || N > MAX_SIZE) {
        printf("Некорректная размерность матрицы\n");
        return 1;
    }

    double matrix[MAX_SIZE][MAX_SIZE];

    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%lf", &matrix[i][j]);
        }
    }


    printf("Матрица:\n");
    printMatrix(matrix, N);


    double det = determinant(matrix, N);
    printf("Определитель: %lf\n", det);

}