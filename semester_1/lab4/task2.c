//Пусть дано целое число а. Вывести в начале значения его битов с четными индексами, а затем с нечетными.

#include <stdio.h>

int main(){
    char a;
    int i=0;
    int cnt, ncnt;
    int q;
    printf("Введите целое число а: ");
    scanf("%d", &a); 
    
    for (i=7;i>=0;i--){
        q=(a>>i)&1;
        printf("%d", q);
    }
    printf("\nЧетные: ");

    for (i=7;i>=0;i-=2){
        q=(a>>i)&1;
        printf("%d", q);
    }
    printf("\nНечетные: ");
    for (i=6;i>=0;i-=2){
        q=(a>>i)&1;
        printf("%d", q);
    }
    printf("\n");


}