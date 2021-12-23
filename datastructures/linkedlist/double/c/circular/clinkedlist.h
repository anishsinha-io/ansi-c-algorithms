#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _CLINKEDLIST_DOUBLE
#define _CLINKEDLIST_DOUBLE

typedef struct CListNode {
  struct CListNode *prev;
  struct CListNode *next;
  int val;
} CListNode;

typedef struct CList {

  // vars
  unsigned int length;
  CListNode *entry;

  // util methods

  void (*print)(const struct CList *);
  bool (*is_empty)(const struct CList *);
  CListNode *(*_create_node)(int val);

  // main methods

  struct CList *(*push_head)(struct CList *, int val);
  struct CList *(*push_tail)(struct CList *, int val);
  struct CList *(*push_index)(struct CList *, int val);

  struct CList *(*delete_head)(struct CList *);
  struct CList *(*delete_tail)(struct CList *);
  struct CList *(*delete_index)(struct CList *, int);

} CList;

CListNode *_create_node(int val) {
  CListNode *new_node = malloc(sizeof(CListNode));
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->val = val;
  return new_node;
}

CList *push_head(CList *self, int val) {
  CListNode *new_node = self->_create_node(val);
  if (self->length == 0) {
    self->entry = new_node;
    new_node->prev = self->entry;
    new_node->next = self->entry;
  } else {
    CListNode *t = self->entry;
    new_node->next = self->entry;
    new_node->prev = self->entry->prev;
    t->prev->next = new_node;
    t->prev = new_node;
    self->entry = new_node;
  }
  self->length++;
  return self;
}

CList *push_tail(CList *self, int val) {
  CListNode *new_node = self->_create_node(val);
  if (self->length == 0) {
    self->entry = new_node;
    new_node->prev = self->entry;
    new_node->next = self->entry;

  } else {
    new_node->next = self->entry;
    new_node->prev = self->entry->prev;
    self->entry->prev->next = new_node;
    self->entry->prev = new_node;
  }
  self->length++;
  return self;
}

void print(const CList *self) {
  CListNode *it = self->entry;
  for (int i = 0; i < self->length; i++) {
    printf("%d ", it->val);
    it = it->next;
  }
}

CList *new_clist() {
  CList *new_clist = malloc(sizeof(CList));
  new_clist->_create_node = _create_node;
  new_clist->length = 0;
  new_clist->push_head = push_head;
  new_clist->push_tail = push_tail;
  new_clist->print = print;
  return new_clist;
}
#endif