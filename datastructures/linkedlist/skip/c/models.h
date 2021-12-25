#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _SLIST_MODELS
#define _SLIST_MODELS

typedef enum SIGN { positive = 1, negative = -1 } SIGN;

typedef struct SListNode {
  double val;
  unsigned int level;
  struct SListNode *prev;
  struct SListNode *next;
  struct SListNode *bottom;
  struct SListNode *top;
  bool is_sentinel;
} SListNode;

typedef struct SListUtil {
  unsigned int (*lg)(unsigned int);
} SListUtil;

typedef struct SList {
  unsigned int length;
  unsigned int max_levels;
  SListNode *head;
  SListNode *tail;
  SListNode *left_sentinel;
  SListNode *right_sentinel;
  SListNode *(*_create_sentinel)(SIGN);
  SListNode *(*_create_node)(double, unsigned int);
  void *(*push_head)(double);
  double *(*delete_head)(void);
  SListUtil *util;
} SList;

#endif