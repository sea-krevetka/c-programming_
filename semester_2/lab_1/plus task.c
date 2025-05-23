#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100

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

void swap(struct student* a, struct student* b) {
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

typedef int (*compareFunc)(struct student, struct student);

int compareByPhys(struct student a, struct student b) {
    return b.phys - a.phys;
}

void QuickSort(struct student arr[], int low, int high, compareFunc cmp) {
    if (low < high) {
        struct student pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (cmp(arr[j], pivot) <= 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pivotIndex = i + 1;

        QuickSort(arr, low, pivotIndex - 1, cmp);
        QuickSort(arr, pivotIndex + 1, high, cmp);
    }
}

int main() {
    srand(time(NULL));
    struct student students[N];

    for (int i = 0; i < N; i++) {
        students[i] = addStudent();
    }

    printf("Студенты до сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
        printf("\n");
    }

    QuickSort(students, 0, N - 1, compareByPhys);

    printf("Студенты после сортировки по физике (от большего к меньшему):\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
        printf("\n");
    }

    return 0;
}
