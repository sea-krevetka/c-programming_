#include "lab10head.h"

int n = 3;

struct lines {
    int x1;
    int x2;
    int y1;
    int y2;
};

void printstruct(struct lines line[], int n) { 
    for (int i = 0; i < n; i++) {
        printf("Coords of line %d: %d %d, %d %d\n", i+1, line[i].x1, line[i].x2, line[i].y1, line[i].y2);
    }
}

void findparameters(int x1,int x2,int y1,int y2){
    float k=((y2-y1)/(x2-x1));
    float m=y1-k*x1;
    printf("y=%.1fx+%.1f\n", k, m);
}
