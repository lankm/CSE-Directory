#include <stdio.h>
#include <math.h>

#define BUFFER_SIZE 20

//returns 0-no overlap, 1-partial or complete.
int overlap(float x1, float y1, float r1, float x2, float y2, float r2) {
    float xDist=x1-x2;
    float yDist=y1-y2;
    float pDist=sqrt(yDist*yDist+xDist*xDist); //gets the linear distance between the two centers.

    if(pDist+r1<=r2) //if circle 1 is inside circle 2
        return 1;
    else if(pDist+r2<=r1) //if circle 2 is inside circle 1
        return 1;
    else
        return 0;
}

int main() {
    float x1=0, y1=0, r1=0;
    float x2=0, y2=0, r2=0;
    char strBuff[BUFFER_SIZE];

    printf("Enter circle 1 parameters (x y radius): ");
    fgets(strBuff, BUFFER_SIZE, stdin);
    sscanf(strBuff,"%f%f%f", &x1, &y1, &r1);

    printf("Enter circle 2 parameters (x y radius): ");
    fgets(strBuff, BUFFER_SIZE, stdin);
    sscanf(strBuff,"%f%f%f", &x2, &y2, &r2);

    int ans = overlap(x1, y1, r1, x2, y2, r2);
    switch(ans) {
        case 0:
            printf("No overlap.");
            break;
        case 1:
            printf("Overlap detected!");
            break;
    }

    return 0;
}
