#include <stdio.h>
#include <stdlib.h>

void init(int** arr, int n) {
    *arr = (int*) malloc(n * sizeof(int)); //changed allocation of dynamic memory
    for (int i = 0; i < n; ++i) {
        (*arr)[i] = i;
    }
}

int main() {
    int* arr = NULL;
    int n = 10;
    init(&arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr); //freeing array and unsigning the pointer
    arr = NULL;
    return 0;
}