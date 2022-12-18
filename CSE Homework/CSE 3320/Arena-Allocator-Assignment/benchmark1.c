#include "mavalloc.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOOPS 9999

int main( int argc, char * argv[] )
{
  uint8_t *arr[LOOPS];
  time_t start, end;
  int noSpace=0;

  start = clock();
  for(int i = 0; i<LOOPS; i++)
  {
    arr[i] = malloc(rand()%40+1);
    if(!arr[i])
      noSpace++;

    if(i>=5 && rand()%2==0) {
      free(arr[i-5]);
      arr[i-5]=0;
    }
  }
  for(int i = 0; i<LOOPS; i+=2)
  {
    if(arr[i-5])
      free(arr[i]);
  }
  end = clock();

  printf("malloc: %d calls. Time: %ld tics. %d nulls\n", LOOPS, end-start, noSpace);


  return 0;
}
