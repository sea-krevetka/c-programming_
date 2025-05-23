#include <stdio.h>
int main(){
    int year;
    printf("Insert year: \n");
    scanf("%d", &year);
    if (year%400==0){
        printf("%d is a leap year", year);
    }else if (year%100==0){
        printf("%d is just a year", year);
    }else if (year%4==0){
        printf("%d is a leap year", year);
    }else {
        printf("%d is just a year", year);
    }
}
