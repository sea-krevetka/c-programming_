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

void swap(struct student* a, struct student* b) {
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct student arr[], int low, int high) {
    int pivot = arr[high].total;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].total > pivot) { // Сортировка по убыванию
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void QuickSort(struct student arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        QuickSort(arr, low, pivotIndex - 1);
        QuickSort(arr, pivotIndex + 1, high);
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

void countingSort(struct student arr[], int n) {
    struct student output[n];
    int max = 300;
    int count[max + 1];

    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++) {
        count[arr[i].total]++;
    }

    for (int i = max - 1; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    for (int i = 0; i < n; i++) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void print_cpu_info() {
    system("cat /proc/cpuinfo | grep 'model name\\|cpu MHz'");
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

    QuickSort(students, 0, N - 1);

    printf("Студенты после сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
        printf("\n");
    }

    measureSortTime(QuickSort, N1);
    measureSortTime(QuickSort, N2);
    measureSortTime(QuickSort, N3);

    printf("\nИнформация о процессоре: \n");
    print_cpu_info();

    printf("\n\nДругие алгоритмы сортировки:\nСортировка вставками:\n");
    insertionSort(students, N);
    measureSortTime(QuickSort, N);

    printf("Сортировка подсчетом:\n");
    countingSort(students, N);
    measureSortTime(QuickSort, N);

    return 0;
}