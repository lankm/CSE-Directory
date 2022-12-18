#include "mavalloc.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOOPS 9999
#define NUM 14

int main( int argc, char * argv[] )
{
  mavalloc_init(NUM*LOOPS, BEST_FIT);
  uint8_t *arr[LOOPS];

  time_t start, end;
  int noSpace=0;

  start = clock();
  for(int i = 0; i<LOOPS; i++)
  {
    arr[i] = mavalloc_alloc(rand()%40+1);
    if(!arr[i])
      noSpace++;

    if(i>=5 && rand()%2==0)
      mavalloc_free(arr[i-5]);
  }
  for(int i = 0; i<LOOPS; i+=2)
  {
    mavalloc_free(arr[i]);
  }
  end = clock();

  printf("Best: %d calls. Time: %ld tics %d nulls\n", LOOPS, end-start, noSpace);


  return 0;
}
