#include <stdio.h>
#include <stdlib.h>

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

int main() {
    struct lines line[3];
    
    line[0].x1 = 1;
    line[0].x2 = 2;
    line[0].y1 = 2;
    line[0].y2 = 4;
    

    line[1].x1 = 1; 
    line[1].x2 = 3; 
    line[1].y1 = 2; 
    line[1].y2 = 0; 
    
    
    line[2].x1 = 1; 
    line[2].x2 = 3; 
    line[2].y1 = 2; 
    line[2].y2 = 0; 
    
    
    printstruct(line, n);

    for (int i=0; i<n; i++){
        printf("Line equation %d: ", i+1);
        findparameters(line[i].x1, line[i].x2,line[i].y1, line[i].y2);
    }

    return 0; 
}
