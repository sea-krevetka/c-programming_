#include "lab10head.h"

int main() {
    int n = 3;
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
