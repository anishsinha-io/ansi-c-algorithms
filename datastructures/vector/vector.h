#include <stdio.h>
#include <stdlib.h>

#ifndef _VECTOR_C
#define _VECTOR_C

typedef struct Vector {
  void **items;
  int capacity;
  int total;
} Vector;

#endif
