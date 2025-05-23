#include <stdio.h>

#define MAX_SIZE 100  

double determinant(double matrix[MAX_SIZE][MAX_SIZE], int n) {
    if (n == 1) {
        return matrix[0][0]; 
    }

    double det = 0;

    for (int col = 0; col < n; col++) {
        double minor[MAX_SIZE][MAX_SIZE];

        for (int i = 1; i < n; i++) {
            for (int j = 0, minor_col = 0; j < n; j++) {
                if (j == col) continue;
                minor[i - 1][minor_col] = matrix[i][j]; //Заполнение минора
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

    printf("Введите элементы расширенной матрицы:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= N; ++j) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    printf("Матрица:\n");
    printMatrix(matrix, N+1);


    double det = determinant(matrix, N);
    if (det == 0) {
        printf("Определитель равен нулю.\n");
    } else {
        printf("Определитель: %lf\n", det);

        double solution[MAX_SIZE];
        for (int i = 0; i < N; ++i) {
            double tempMatrix[MAX_SIZE][MAX_SIZE];

            // Копирование оригинальной матрицы и замена i-го столбца на свободные члены
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    tempMatrix[j][k] = matrix[j][k];
                }
                tempMatrix[j][i] = matrix[j][N];
            }
            solution[i] = determinant(tempMatrix, N) / det;
        }
        printf("Решения:\n");
        for (int i = 0; i < N; ++i) {
            printf("x[%d] = %lf\n", i, solution[i]);
        }
    }

    return 0;
}
