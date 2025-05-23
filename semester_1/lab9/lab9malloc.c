#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int findMaxEli(int **matrix, int N) {
    int maxtmp = matrix[0][0];
    int mi = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > maxtmp) {
                maxtmp = matrix[i][j];
                mi = i;
            }
        }
    }
    return mi;
}

int findMaxElj(int **matrix, int N) {
    int maxtmp = matrix[0][0];
    int mj = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > maxtmp) {
                maxtmp = matrix[i][j];
                mj = j;
            }
        }
    }
    return mj;
}

int countZeros(int **matrix, int N) {
    int cnt1 = 0;
    for (int i = 0; i < N; i++) {
        int cnt2 = 0;
        for (int j = 0; j < N; j++) { 
            if (matrix[i][j] == 0) {
                cnt2++;
            }
        }
        if (cnt2 > 0) {
            cnt1++;
        }
    }
    return cnt1;
}

void diagonalBackw(int **matrix, int N) {
    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            if (i == j) {
                printf("%d ", matrix[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printMatrix(int **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N;

    printf("Type size of matrix: ");
    if (scanf("%d", &N) != 1) {
        exit(0);
    }
    if (N < 1 || N > MAX_SIZE) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    int flag = 0;
    printf("Fill matrix manually (1) or randomly (0)?\nChoose 1 or 0: ");
    if (scanf("%d", &flag) != 1 || (flag != 0 && flag != 1)) {
        printf("Invalid type.\n");
        return 0;
    }


    int **matrix = (int **)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            if (flag == 0) {
                matrix[i][j] = rand() % 100;
            } else {
                printf("Enter element [%d][%d]: ", i, j);
                if (scanf("%d", &matrix[i][j]) != 1) {
                    exit(0);
                }
            }
        }
    }

    int maxMatEli = findMaxEli(matrix, N);
    int maxMatElj = findMaxElj(matrix, N);
    
    int **matrixB = (int **)malloc((N - 1) * sizeof(int*));
    for (int i = 0; i < N - 1; i++) {
        matrixB[i] = (int *)malloc((N - 1) * sizeof(int));
    }

    for (int i = 0, bi = 0; i < N; i++) {
        if (i == maxMatEli) continue; 
        for (int j = 0, bj = 0; j < N; j++) {
            if (j == maxMatElj) continue; 
            matrixB[bi][bj] = matrix[i][j];
            bj++;
        }
        bi++;
    }

    printf("Original Matrix:\n");
    printMatrix(matrix, N);

    printf("Matrix B:\n");
    printMatrix(matrixB, N - 1); 
    int strZeros = countZeros(matrixB, N - 1); 
    printf("Number of rows with zeros in matrix B: %d\n", strZeros);
    printf("Diagonal of matrix B in reverse order:\n");
    diagonalBackw(matrixB, N - 1);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    for (int i = 0; i < N - 1; i++) {
        free(matrixB[i]);
    }
    free(matrixB);

    return 0;
}
