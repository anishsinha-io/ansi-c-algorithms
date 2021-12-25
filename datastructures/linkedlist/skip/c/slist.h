#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _SLIST
#define _SLIST

typedef enum SIGN { positive = 1, negative = -1 } SIGN;

typedef struct SListNode {
  double val;
  struct SListNode *prev;
  struct SListNode *next;
  struct SListNode *bottom;
  struct SListNode *top;
  bool is_sentinel;
} SListNode;

typedef struct SList {
  unsigned int length;
  unsigned int max_levels;
  SListNode *head;
  SListNode *tail;
  SListNode *left_sentinel;
  SListNode *right_sentinel;
  SListNode *(*_create_sentinel)(SIGN);
  SListNode *(*_create_node)(int);
} SList;

SListNode *_create_sentinel(SIGN sign) {
  SListNode *new_sentinel = malloc(sizeof(SListNode));
  new_sentinel->val = sign * INFINITY;
  new_sentinel->bottom = new_sentinel->top = new_sentinel->next =
      new_sentinel->prev = NULL;
  new_sentinel->is_sentinel = true;
  return new_sentinel;
}

SListNode *_create_node(double val) {
  SListNode *new_node = malloc(sizeof(SListNode));
  new_node->val = val;
  new_sentinel->bottom = new_sentinel->top = new_sentinel->next =
      new_sentinel->prev = NULL;
  new_sentinel->is_sentinel = false;
}

SList *create_slist() {
  SList *new_slist = malloc(sizeof(SList));
  new_slist->left_sentinel = new_slist->_create_sentinel(-1);
  new_slist->right_sentinel = new_slist->_create_sentinel(1);
  new_slist->left_sentinel->next = new_slist->right_sentinel;
  new_slist->right_sentinel->prev = new_slist->left_sentinel;
  new_slist->length = 0;
  new_slist->head = new_slist->tail = NULL;
  return new_slist;
}

#endif