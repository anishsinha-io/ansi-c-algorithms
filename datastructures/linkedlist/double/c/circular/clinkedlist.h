#include <stdio.h>
#include <stdlib.h>

#ifndef _CLINKEDLIST
#define _CLINKEDLIST

typedef struct CListNode {
  int val;
  struct CListNode *next;
} CListNode;

typedef struct CList {
  unsigned int length;
  CListNode *tail;
  void (*print)(const struct CList *);
} CList;

#endif