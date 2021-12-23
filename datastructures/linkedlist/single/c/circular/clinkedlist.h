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
  CListNode *head;
  CListNode *(*_create_node)(int);
  void (*print)(const struct CList *);
  bool (*is_empty)(const struct CList *);
  struct CList *(*push_head)(struct CList *, int);
  struct CList *(*push_tail)(struct CList *, int);
} CList;

CListNode *_create_node(int val) {
  CListNode *new_node = malloc(sizeof(CListNode));
  new_node->next = NULL;
  new_node->val = val;
  return new_node;
}

bool is_empty(const CList *self) { return self->length == 0; }

CList *push_head(CList *self, int val) {
  CListNode *new_node = self->_create_node(val);
  if (self->is_empty(self)) {
    printf("here");
    self->head = new_node;
    new_node->next = self->head;
  } else {
    CListNode *t = self->head;
    while (t->next != self->head) {
      t = t->next;
    }
    new_node->next = self->head;
    self->head = new_node;
    t->next = self->head;
  }
  self->length++;
  return self;
}

CList *push_tail(CList *self, int val) {
  CListNode *new_node = self->_create_node(val);
  if (self->is_empty(self)) {
    self->head = new_node;
    new_node->next = self->head;
  } else {
    CListNode *t = self->head;
    while (t->next != self->head) {
      t = t->next;
    }
    t->next = new_node;
    new_node->next = self->head;
  }
  self->length++;
  return self;
}

CList *push_index(CList *self, int val) { return self; }

CList *delete_head(CList *self) { return self; }

CList *delete_tail(CList *self) { return self; }

CList *delete_index(CList *self, int index) { return self; }

CList *new_clist() {
  CList *new_clist = malloc(sizeof(CList));
  new_clist->push_head = push_head;
  new_clist->push_tail = push_tail;
  // new_clist->push_index = push_index;
  // new_clist->delete_head = delete_head;
  // new_clist->delete_tail = delete_tail;
  // new_clist->delete_index = delete_index;

  new_clist->is_empty = is_empty;
  // new_clist->print = print;
  return new_clist;
}

#endif