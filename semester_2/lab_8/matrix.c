#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

double** createMatrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double determinant(double** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }

    double det = 0;
    double** minor = createMatrix(n - 1);

    for (int col = 0; col < n; col++) {
        for (int i = 1; i < n; i++) {
            for (int j = 0, minor_col = 0; j < n; j++) {
                if (j == col) continue;
                minor[i - 1][minor_col] = matrix[i][j];
                minor_col++;
            }
        }
        double sign = (col % 2 == 0) ? 1 : -1;
        det += sign * matrix[0][col] * determinant(minor, n - 1);
    }

    freeMatrix(minor, n - 1);
    return det;
}

void printMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}