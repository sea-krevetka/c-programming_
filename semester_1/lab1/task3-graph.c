#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
    float ux;
    float uy;
    printf("well 7th task it is\n");
    printf("insert coords x y: ");
    scanf("%f %f", &ux, &uy);
    if (uy<=2 && uy>=0 && uy>=(-2*ux-2) && uy>=(2*ux-2)){
        printf("yay its inside the trapezoid yaapiiiiiiii\n");
    }else{  
        printf("oh no it got out\n");
    }



}
