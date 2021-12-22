#include <stdbool.h>
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
  CListNode *current;
  CListNode *(*_create_node)(int);
  void (*print)(const struct CList *);
  bool (*is_empty)(const struct CList *);
  struct CList *(*push_start)(struct CList *, int);
  struct CList *(*push_tail)(struct CList *, int);
} CList;

bool is_empty(const CList *self) { return self->length == 0; }

CListNode *_create_node(int val) {
  CListNode *new_node = malloc(sizeof(CListNode));
  new_node->next = NULL;
  new_node->val = val;
  return new_node;
}

CList *push_tail(CList *self, int val) {
  CListNode *new_node = self->_create_node(val);
  if (self->is_empty(self)) {
    self->tail = new_node;
    new_node->next = self->tail;
  } else {
    CListNode *t = self->tail;
    t->next = new_node;
    new_node->next = t;
    self->tail = new_node;
  }
  return self;
}

CList *push_start(CList *self, int val) {
  CListNode *new_node = self->_create_node(val);
  if (self->is_empty(self)) {
    self->tail = new_node;
    new_node->next = self->tail;
  } else {
    CListNode *t = self->tail;
    while (t->next != t) {
      t = t->next;
    }
    t->next = new_node;
    new_node->next = self->tail;
  }
  return self;
}

CList *new_clist() {
  CList *new_list = malloc(sizeof(CList));
  new_list->is_empty = is_empty;
  new_list->_create_node = _create_node;
  new_list->push_tail = push_tail;
  new_list->push_start = push_start;
  return new_list;
}

#endif