
//just a main method I can fiddle with

#include "mavalloc.c"
#include "tinytest.h"
#include <stdio.h>
#include <string.h>

// debug helpers
void print_node(Node n)
{
  printf("size: %d\n", n.size);
  printf("free: %d\n", n.type);
  printf("ptr: %p\n", n.arena);
  printf("next: %d\n", n.next);
  printf("prev: %d\n", n.prev);
}
void print_array()
{
  int total = 0;
  for(int i = 0; i<MAX_NODES; i++)
  {
      printf("--index: %d--\n", i);
      print_node(blocks[i]);
      printf("\n");
      total++;
  }
  printf("Array Total: %d\n", total);
}
void print_used()
{
  int total=0;
  int i=head_used;
  do
  {
    if(i != -1)
    {
      print_node(blocks[i]);
      printf("\n");
      i = blocks[i].next;
      total++;
    }
  } while(i != head_used);
  printf("Used Total: %d\n", total);
}
void print_nused()
{
  int total = 0;
  int i=head_nused;
  do {
    if(i != -1)
    {
      print_node(blocks[i]);
      printf("\n");
      i = blocks[i].next;
      total++;
    }
  } while(i != head_nused);
  printf("NUsedTotal: %d\n", total);
}

int main(int argc, const char **argv) {

    mavalloc_init( 65535, BEST_FIT );
  char * ptr = ( char * ) mavalloc_alloc ( 65530 );

  int size = mavalloc_size();

  // If you failed here your allocation on line 13 failed
  TINYTEST_ASSERT( ptr ); 

  // If you failed here your linked list did not have a single node
  // check your mavalloc_alloc or mavalloc_size
  TINYTEST_EQUAL( size, 1); 
  mavalloc_destroy( );
  return 1;
}
