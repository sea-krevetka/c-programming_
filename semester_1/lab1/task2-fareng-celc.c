#include <stdio.h>
float factor=1.8;
int main(){
    float temp;
    char s;
    printf("Isert temp: ");
    scanf("%f%c", &temp, &s);
    if (s=='c' || s=='C'){
        printf("%.2fc is equeal %.2ff\n", temp, temp*factor+32);
    }else if (s=='f' || s=='F'){
        printf("%.2ff is equeal %.2fc\n", temp, (temp-32)/factor);
    }else{
        printf("invalid character\n");}
}
