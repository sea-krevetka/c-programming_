#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10
#define N1 100
#define N2 10000
#define N3 100000

struct student {
    char name[64];
    int math;
    int phys;
    int inf;
    int total; 
};

char NAMES[][64] = {"hehe", "nehehe", "ыктывкарурмек"};

struct student addStudent() {
    struct student newStudent;
    int math, phys, inf;

    math = rand() % 100 + 1;
    phys = rand() % 100 + 1;
    inf = rand() % 100 + 1;
    int randomIndex = rand() % (sizeof(NAMES) / sizeof(NAMES[0]));

    strcpy(newStudent.name, NAMES[randomIndex]);
    newStudent.math = math;
    newStudent.phys = phys;
    newStudent.inf = inf;
    newStudent.total = math + phys + inf;

    return newStudent;
}

void printStudentInfo(struct student s) {
    printf("Имя: %s\n", s.name);
    printf("Математика: %d\n", s.math);
    printf("Физика: %d\n", s.phys);
    printf("Информатика: %d\n", s.inf);
    printf("Общий балл: %d\n", s.total);
}

void insertionSort(struct student arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct student key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].total < key.total) { // Сортировка по убыванию
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void measureSortTime(void (*algorithm)(struct student*, int, int), int n) {
    struct student* students = malloc(n * sizeof(struct student));
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        students[i] = addStudent();
    }

    clock_t start = clock();
    algorithm(students, 0, n - 1);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время сортировки для N=%d: %f секунд\n", n, time_spent);

    free(students);
}

int main() {
    srand(time(NULL));
    struct student students[N];
    printf("Сортировка подсчетом:\n");
    countingSort(students, N);
    measureSortTime(QuickSort, N);
}