#include <stdio.h>
#include <assert.h>
#include "matrix.h"

void print_test_header(const char* test_name) {
    printf("\n=== Running %s tests ===\n", test_name);
}

void print_test_case(const char* description, int passed) {
    printf("    %-40s [%s]\n", description, passed ? "PASSED" : "FAILED");
}

void test_determinant() {
    print_test_header("determinant");
    int total_tests = 0;
    int passed_tests = 0;

    // Test 1x1 matrix
    {
        total_tests++;
        double** matrix = createMatrix(1);
        matrix[0][0] = 5;
        
        double expected = 5;
        double result = determinant(matrix, 1);
        int passed = (result == expected);
        passed_tests += passed;
        print_test_case("1x1 matrix", passed);
        
        freeMatrix(matrix, 1);
    }

    // Test 2x2 matrix
    {
        total_tests++;
        double** matrix = createMatrix(2);
        matrix[0][0] = 1; matrix[0][1] = 2;
        matrix[1][0] = 3; matrix[1][1] = 4;
        
        double expected = -2; // (1*4 - 2*3)
        double result = determinant(matrix, 2);
        int passed = (result == expected);
        passed_tests += passed;
        print_test_case("2x2 matrix", passed);
        
        freeMatrix(matrix, 2);
    }

    // Test 3x3 matrix
    {
        total_tests++;
        double** matrix = createMatrix(3);
        matrix[0][0] = 2;  matrix[0][1] = -3; matrix[0][2] = 1;
        matrix[1][0] = 2;  matrix[1][1] = 0;  matrix[1][2] = -1;
        matrix[2][0] = 1;  matrix[2][1] = 4;  matrix[2][2] = 5;
        
        double expected = 49;
        double result = determinant(matrix, 3);
        int passed = (result == expected);
        passed_tests += passed;
        print_test_case("3x3 matrix", passed);
        
        freeMatrix(matrix, 3);
    }

    // Test 4x4 identity matrix
    {
        total_tests++;
        double** matrix = createMatrix(4);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = (i == j) ? 1 : 0;
            }
        }
        
        double expected = 1;
        double result = determinant(matrix, 4);
        int passed = (result == expected);
        passed_tests += passed;
        print_test_case("4x4 identity matrix", passed);
        
        freeMatrix(matrix, 4);
    }

    printf("\n%d/%d tests passed\n", passed_tests, total_tests);
}

void test_printMatrix() {
    print_test_header("printMatrix");
    
    // Test 2x2 matrix
    {
        double** matrix = createMatrix(2);
        matrix[0][0] = 1.5;   matrix[0][1] = 2.25;
        matrix[1][0] = 3.75;  matrix[1][1] = 4.125;
        
        printf("\nExpected output for 2x2 matrix:\n");
        printf("  1.5000   2.2500 \n");
        printf("  3.7500   4.1250 \n");
        
        printf("Actual output:\n");
        printMatrix(matrix, 2);
        
        freeMatrix(matrix, 2);
    }

    // Test 1x1 matrix
    {
        double** matrix = createMatrix(1);
        matrix[0][0] = 3.14159;
        
        printf("\nExpected output for 1x1 matrix:\n");
        printf("  3.1416 \n");
        
        printf("Actual output:\n");
        printMatrix(matrix, 1);
        
        freeMatrix(matrix, 1);
    }
    
    printf("\nVisual tests require manual verification\n");
}

int main() {
    printf("\nStarting matrix tests...\n");
    test_determinant();
    test_printMatrix();
    printf("\nAll tests completed!\n");
    return 0;
}