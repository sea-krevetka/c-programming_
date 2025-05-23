#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrimary(int m){
    int cnt=0;
    for (int i=2; i<=sqrt(m); i++){
        if (m%i==0){
            cnt++;
            //printf("%d", m);
        } //проверка на количество делителей у числа, если cnt==0, то числа простое
    }
    if (cnt==0){
        return true;
    }else{
        return false;
    }
}

void print_arr(int n, int array[n]){
    int lecnt=0;
    int summ=0;
    printf("[");
    for (int i=0; i<n; i++){
        printf("%d ", array[i]); //вывод элементов массива
        summ=summ+array[i]; //сумма элементов массива
        if (isPrimary(array[i])==true){
            lecnt++;} // запуск функции на проверку простого числа
    }
    printf("]\n");
    printf("Количество простых чисел: %d \n", lecnt);
    printf("Среднее арифметическое: %d \n", (summ/n));
    
}





int main(){
    //isPrimary(5);

    int n;
    printf("Введите размер массива: ");
    scanf("%d", &n);
    
    int m=n/2;
    int X[n];
    int Y[(n/2)]; //размер второго массива
    
    printf("Введите элементы массива: "); //через enter каждый
    int q=0;
    for (int i=0; i<n; i++){
        scanf("%d", &q);
        X[i]=q; //запись введеных чисел в массив
    }
    print_arr(n, X);
    
    int f=0;
    for (int i=1; i<sizeof(X)/4; i+=2){ //запись элементов с шагом 2 - каждый второй элемент
        Y[f]=X[i];
        f++;
    }
    print_arr(m, Y);
    
    
    
}
