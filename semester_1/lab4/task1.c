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
        if (q==1){
            cnt++;
        }else {ncnt++;}
        printf("%d", q);
    }

    printf("\nКоличество единиц: %d\nКоличество нулей: %d", cnt, ncnt);


}