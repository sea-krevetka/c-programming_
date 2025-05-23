#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 10

struct route {
    char destination[50];
    int trainnum; 
    int number[2];
};

const char* cities[] = {
    "Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Казань"
};

void search(struct route array[N], int choice) {
    char searchDestination[50];
    int searchTrainNum = 0; 
    int searchNumber[2];
    int found = 0;

    switch (choice) {
        case 1:
            printf("Введите пункт назначения: ");
            scanf("%s", searchDestination);
            for (int i = 0; i < N; i++) {
                if (strcmp(array[i].destination, searchDestination) == 0) {
                    printf("[%d] Пункт назначения %s \nНомер поезда %d \nВремя отправления %02d:%02d\n",
                           i, array[i].destination, array[i].trainnum, array[i].number[0], array[i].number[1]);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Введите номер поезда для поиска: ");
            scanf("%d", &searchTrainNum);
            for (int i = 0; i < N; i++) {
                if (array[i].trainnum == searchTrainNum) {
                    printf("[%d] Пункт назначения %s \nНомер поезда %d \nВремя отправления %02d:%02d\n",
                           i, array[i].destination, array[i].trainnum, array[i].number[0], array[i].number[1]);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Введите время отправления (часы и минуты) для поиска: ");
            scanf("%d %d", &searchNumber[0], &searchNumber[1]);
            for (int i = 0; i < N; i++) {
                if (array[i].number[0] == searchNumber[0] && array[i].number[1] == searchNumber[1]) {
                    printf("[%d] Пункт назначения %s \nНомер поезда %d \nВремя отправления %02d:%02d\n",
                           i, array[i].destination, array[i].trainnum, array[i].number[0], array[i].number[1]);
                    found = 1;
                }
            }
            break;
        default:
            printf("Неверный выбор.\n");
            return;
    }

    if (!found) {
        printf("Подходящий маршрут не найден\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: ./исполняемыйфайл.out бинфайл.dat\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "wb"); //запись в бинарном
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        exit(1);
    }

    srand(time(NULL));

    struct route array[N];
    printf("\nЗапись в бинарный файл...\n");
    for (int i = 0; i < N; i++) {
        array[i].trainnum = rand() % 1000; 
        strncpy(array[i].destination, cities[rand() % 5], sizeof(array[i].destination) - 1); // Исправлено: корректный выбор города
        array[i].number[0] = rand() % 24;
        array[i].number[1] = rand() % 60;
        fwrite(&array[i], sizeof(struct route), 1, file);
        printf("[%d] Пункт назначения %s \nНомер поезда %d \nВремя отправления %02d:%02d\n",
            i, array[i].destination, array[i].trainnum, array[i].number[0], array[i].number[1]);
    }

    fclose(file);

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        exit(1);
    }
    printf("\nЧтение из бинарного файла...\n");
    fread(array, sizeof(struct route), N, file);
    for (int i = 0; i < N; i++) {
        printf("[%d] Пункт назначения %s \nНомер поезда %d \nВремя отправления %02d:%02d\n",
                           i, array[i].destination, array[i].trainnum, array[i].number[0], array[i].number[1]);
    }
    fclose(file);

    printf("По какому из полей выполнить поиск: 1 - пункт назначения, 2 - номер поезда, 3 - время отправления\n");
    int choose;
    scanf("%d", &choose);
    search(array, choose);
    return 0;
}
