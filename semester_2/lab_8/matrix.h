#ifndef MATRIX_H
#define MATRIX_H

double determinant(double** matrix, int n);
void printMatrix(double** matrix, int n);
double** createMatrix(int n);
void freeMatrix(double** matrix, int n);

#endif