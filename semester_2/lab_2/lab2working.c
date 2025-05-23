#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
    struct node *prev;
};
typedef struct node node_t;

node_t* newNode(int data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void append(node_t **head, int data){
    node_t *new = newNode(data);
    if (*head == NULL){
        *head = new;
        return;
    }
    node_t *cur = *head;
    while (cur->next != NULL){
        cur = cur->next;
    }
    cur->next = new;
}

void printList(node_t *head) {
    node_t* cur = head;
    while (cur != NULL) {
        printf("Data: %d\n", cur->data);
        printf("Next: %p\n", cur->next);
        printf("Prev: %p\n\n", cur->prev);
        cur = cur->next;
    }
    printf("\n\n");
}

void freeList(node_t* head) {
    node_t* cur = head;
    while (cur != NULL) {
        node_t* next = cur->next;
        free(cur);
        cur = next;
    }
}

int main() {
    node_t* list1 = NULL;
    node_t* list2 = NULL;
    int data;

    printf("Введите элементы первого списка (0 для завершения):\n");
    while (1) {
        scanf("%d", &data);
        if (data == 0) {
            break;
        }
        append(&list1, data);
    }
    
    printf("Введите элементы второго списка (0 для завершения):\n");
    while (1) {
        scanf("%d", &data);
        if (data == 0) {
            break;
        }
        append(&list2, data);
    }

    node_t* cur1 = list1;
    node_t* cur2 = list2;

    while (cur1 != NULL && cur2 != NULL) {
        cur1->prev = cur2;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    /*if ((cur1 == NULL && cur2 != NULL) || (cur1 != NULL && cur2 == NULL)) {
        cur1->prev = cur2;
        break;
    }*/

    printf("Вывод первого списка:\n");
    printList(list1);
    
    printf("Вывод второго списка:\n");
    printList(list2);

    node_t* S = newNode(-1);
    S->next = list1;

    node_t* cur = S;
    char input;
    int flagS=0;
    printf("Перемещение по списку (WASD/2468), Q выход, S для перехода на следующий элемент второго списка:\n");
    while (1) {
        printf("Текущее значение: %d\n", cur->data);
        scanf(" %c", &input);
        if (input == 'D' || input == 'd') {
            if (cur->next != NULL) {
                cur = cur->next;
            }
        }

        if ((input == 'S' || input == 's')&&(cur->prev!=NULL)){
            if (cur->prev!=NULL){
                cur = cur->prev;
                flagS=1;
            }
        }
        
        /*if (cur->prev!=NULL){
            if (input == 'S' || input == 's') {
                cur = cur->prev;
            }
        }*/
        
        if (cur->next==NULL){
            printf("Текущее значение: %d\n", cur->data);
            printf("Тупик. Начало T:\n");
        }
        if ((cur->prev==NULL)&&(flagS==0)){
            printf("Текущее значение: %d\n", cur->data);
            printf("Тупик. Начало T:\n");
        }

        if (input == 'T' || input == 't'){
            cur = S;
        }
    }
    




    freeList(list1);
    freeList(list2);
    free(S);
    return 0;
}


