//1111111
//1222221
//1233321
//1234321
//1233321
//1222221
//1111111

#include <stdio.h>

int main() {
    int height, i, j, min;

    //printf("Введите высоту: ");
    //scanf("%d", &height);
    height=7;

    for (i=1; i<=height; i++) {
        for (j=1; j <= height; j++){
            if (i < j) {
                min=i;
            }else{
                min=j;
            }

            if (min > height-j+1){
                min=height-j+1;
            }

            if (min > height-i+1) {
                min = height-i+1;
            }printf("%d", min);
        }
        printf("\n");
    }
    
    return 0;
}