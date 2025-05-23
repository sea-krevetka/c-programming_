#include <stdio.h>
int n;
int m;
int i;

int a;
int b;
int main(){
    printf("task 1\n");
    scanf("%d %d", &n, &m);
    for (i=n; !(i%n==0 && m%i==0); i--);
    printf("GCD for nums %d %d is %d\n", n, m, i);

    printf("task 2\n");
    scanf("%d %d", &a, &b);
    for (n=a; (n%a!=0) || (n%b!=0); n++);
    printf("LCM for nums %d %d is %d\n", a, b, n);

    printf("task 3\n");
    scanf("%d", &a);
    for (n=2; n<a; n++){
        if (a%n==0) break;
    }
    if (n==a){ 
        puts("1");
        printf("LD %d is itself (%d)\n", a, n);
    }else{ 
        puts("0");
        printf("LD %d is %d\n", a, n);
    }

    printf("task 4\n");
    scanf("%d", &a);
    for (n=2; n<a && a%n!=0; n++);
    if (n==a){
        puts("1");
        printf("%d is a prime number\n", a);
    } 
    else{
        puts("0");
        printf("SD %d is %d\n", a, n);
    }

    printf("task 5\n");
    int s;
    scanf("%d", &a);
    for (s=0, n=2; n<a; n++){
        if (a%n==0){
            s++;
        }
    }
    if (s==0){
        puts("1");
        printf("%d is a prime number\n", a);
    }else{
        puts("0");
        printf("divisor amount for %d is %d", a,s);
    }

}
