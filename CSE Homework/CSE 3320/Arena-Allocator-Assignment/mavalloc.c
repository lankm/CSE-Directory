/* The MIT License (MIT)
 * 
 * Copyright (c) 2021, 2022 Trevor Bakker 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES UTA OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "mavalloc.h"
#include <stdlib.h>
#include <stdint.h>

#define MAX_NODES 10000

enum TYPE{P, H};
typedef struct node {
  size_t size;
  enum TYPE type;
  void *arena;
  int next;
  int prev;
} Node;

// core variables
Node *blocks;
int nodes = 0;
int head_nused = -1;
int head_used = -1;

// next-0, best-1, worst-2, first-3
enum ALGORITHM algo = -1;

// algorithm variables
int start = -1;

/* basic stitching of DLLs */
void stitchPop(int i)
{
  // stitch i.prev to i.next
  blocks[ blocks[i].prev ].next = blocks[i].next;
  blocks[ blocks[i].next ].prev = blocks[i].prev;
}
void stitchPush(int i, int j)
{
  // pushes to after instead of before
  i = blocks[i].next;

  // stitching nused tail <-> i
  blocks[ blocks[i].prev ].next=j;
  blocks[j].prev = blocks[i].prev;
  // stitching nused i <-> j
  blocks[i].prev = j;
  blocks[j].next = i;
}
/* tossing between two LLs */
void throwBlock(int ball)
{
  // throwing non-existant ball
  if( ball == -1 )
  {
    //printf(">>== No Ball!! ==<<\n");
    return;
  }

  // throwing ball from 'used'
  if( ball != blocks[ball].next )
  {
    // if removing head, shift head to next
    if( ball == head_used )
    {
      head_used = blocks[ball].next;
    }
    // stitch. pops ball
    stitchPop(ball);
  }
  else
  {
    // DO NOT remove single node LL
    //printf(">>== Destroyed used LL!! ==<<\n");
    head_used = -1;
  }

  // catching ball in 'nused'
  if( head_nused != -1 )
  {
    // stitching. push ball to nused
    stitchPush(head_nused, ball);
  }
  else
  {
    // nused had no balls
    blocks[ball].prev = ball;
    blocks[ball].next = ball;
    head_nused = ball;
  }
}
int catchBlock(int glove)
{
  // temp variables
  int temp_head;

  // throwing ball from 'nused'
  if(head_nused != -1)
  {
    temp_head = head_nused;

    // if not only one in LL
    if( head_nused != blocks[head_nused].next )
    {
      // stitch. pops head_nused
      stitchPop(head_nused);
      // rebase
      head_nused = blocks[head_nused].next;
    }
    else
    {
      // last node popped from nused
      head_nused = -1;
    }
  }
  else
  {
    // no empty blocks
    // printf("NULL\n");
    return -1;
  }

  // catching ball in 'used'
  if(glove != -1)
  {
    // stitch
    stitchPush(glove, temp_head);
  }
  else
  {
    // DO NOT generate new LL... unless
    //printf(">>== Forked LL created!! ==<<\n");
    blocks[temp_head].next = temp_head;
    blocks[temp_head].prev = temp_head;
  }

  // return old head_nused
  return temp_head;
}

int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{

  size = ALIGN4( size );

  // setting algo
  algo = algorithm;

  // init blocks array
  blocks = (Node*) malloc(MAX_NODES * sizeof(Node));
  for(int i = 0; i<MAX_NODES; i++)
  {
    blocks[i].size = 0;
    blocks[i].type = H;
    blocks[i].arena = NULL;

    blocks[i].next = i+1;
    blocks[i].prev = i-1;
  }

  // LL setup
  head_nused = 1; // nodes where (size = 0)
  head_used = 0; // nodes that are P or H(size > 0)

  // head_used setup
  blocks[ head_used ].size = size;
  blocks[ head_used ].arena = malloc(size);
  blocks[ head_used ].next = head_used;
  blocks[ head_used ].prev = head_used;
  if( !blocks[head_used].arena ) // if error
    return -1;
  nodes = 1;
  start = head_used;

  // tail-head_nused stitch
  blocks[MAX_NODES-1].next = head_nused;
  blocks[head_nused].prev = MAX_NODES-1;

  return 0;
}
void mavalloc_destroy()
{
  // core function
  free(blocks[0].arena);
  free(blocks);
  blocks = NULL;

  // resetting variables
  nodes = 0;
  head_nused = -1;
  head_used = -1;
  algo = -1;
  start = -1;

  return;
}

void * node_alloc( size_t size, int i )
{
  // return variable
  void *ptr = NULL;

  // size of next allocated block
  int leftover = blocks[i].size-size;

  // if space left over
  if(leftover > 0)
  {
    // get new block
    int block = catchBlock(i);
    // all blocks used
    if(block == -1)
      return NULL;

    // new block setup
    blocks[block].type = H;
    blocks[block].arena = blocks[i].arena + (blocks[i].size - leftover);
    blocks[block].size = leftover;
    nodes++;

    // returned block setup
    blocks[i].type = P;
    blocks[i].size -= leftover;
    ptr = blocks[i].arena;
  }
  // nothing left over
  else
  {
    // convert entire node to return
    blocks[i].type = P;
    ptr = blocks[i].arena;
  }

  return ptr;
}
void * next_alloc( size_t size, int i )
{
  // return variable
  void *ptr = NULL;

  // looping through blocks
  int end = i;
  do
  {
    // if free and large enough
    if( blocks[i].type==H && blocks[i].size>=size )
    {
      // split node if needed
      ptr = node_alloc(size, i);
      break;
    }

    // next block
    i = blocks[i].next;
  } while( i != end );

  start = i;
  return ptr;
}
void * first_alloc(size_t size)
{
  // next_alloc starting from the first
  return next_alloc(size, head_used);
}
void * best_alloc( size_t size)
{
  // return variable
  void *ptr = NULL;

  // best fit location data
  int smallest = -1;
  size_t smallest_size = SIZE_MAX;

  // looping through blocks
  int i = head_used;
  do
  {
    
    // if free and large enough
    if( blocks[i].type==H && blocks[i].size>=size )
    {
      // if found node can fit better
      if(blocks[i].size < smallest_size)
      {
        smallest = i;
        smallest_size = blocks[i].size;
      }
    }

    // next block
    i = blocks[i].next;
  } while( i != head_used );

  // if spot large enough
  if(smallest != -1)
  {
    // actually allocate and split if needed
    ptr = node_alloc(size, smallest);
  }

  return ptr;
}
void * worst_alloc( size_t size)
{
  // return variable
  void *ptr = NULL;

  // best fit location data
  int largest = -1;
  size_t largest_size = 0;

  // looping through blocks
  int i = head_used;
  do
  {
    // if free and large enough
    if( blocks[i].type==H && blocks[i].size>=size )
    {
      // if found node can fit better
      if(blocks[i].size > largest_size)
      {
        largest = i;
        largest_size = blocks[i].size;
      }
    }

    // next block
    i = blocks[i].next;
  } while( i != head_used );

  // if spot large enough
  if(largest != -1)
  {
    // actually allocate and split if needed
    ptr = node_alloc(size, largest);
  }

  return ptr;
}
void * mavalloc_alloc( size_t size )
{
  size = ALIGN4( size );
  // goto algorithm function
  switch (algo)
  {
    case FIRST_FIT:
      return first_alloc(size);
    case NEXT_FIT:
      return next_alloc(size, start);
    case BEST_FIT:
      return best_alloc(size);
    case WORST_FIT:
      return worst_alloc(size);

    // not initialized
    default:
      //printf(">>== Not Initialized!! ==<<\n");
      return NULL;
  }
}

void mavalloc_free( void * ptr )
{
  // start from beginning 
  int i = head_used;
  do
  {
    // if ptr is found
    if( blocks[i].arena == ptr )
    {
      // free
      blocks[i].type = H;


      // if next is free and not the head
      if( blocks[ blocks[i].next ].type == H && blocks[i].next!=head_used)
      {
        blocks[i].size += blocks[ blocks[i].next ].size;
        throwBlock(blocks[i].next);
        nodes--;
      }
      // if previous is free and not the tail
      if( blocks[ blocks[i].prev ].type == H && i!=head_used)
      {
        blocks[ blocks[i].prev ].size += blocks[i].size;
        throwBlock(i);
        nodes--;
      }
      

      break;
    }

    // next block
    i = blocks[i].next;
  } while( i != head_used );

  return;
}

int mavalloc_size( )
{
  return nodes;
}
