#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>



struct lines {
    int x1;
    int x2;
    int y1;
    int y2;
};

void printstruct(struct lines line[], int n);
void findparameters(int x1,int x2,int y1,int y2);

#endif