/**
 * @author Anish Sinha (anishsinha0128@gmail.com)
 * @brief Implements a doubly linked list using objected-oriented patterns in C
 *        by leveraging function pointers and structs.
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef _DLINKEDLIST
#define _DLINKEDLIST

typedef struct DListNode {
  int val;
  struct DListNode *prev;
  struct DListNode *next;
} DListNode;

typedef struct DList {
  DListNode *head;
  DListNode *tail;
  unsigned int length;
  void (*print)(const struct DList *);
  void (*del)(const struct DList *);
  DListNode *(*_create_node)(int);
  struct DList *(*push_start)(struct DList *, int);
  struct DList *(*push_tail)(struct DList *, int);
  struct DList *(*push_index)(struct DList *, int, int);
  struct DList *(*delete_head)(struct DList *);
  struct DList *(*delete_tail)(struct DList *);
  struct DList *(*delete_index)(struct DList *, int);
} DList;

void print_list(const DList *self) {
  DListNode *it = self->head;
  while (it != NULL) {
    printf("%d\n", it->val);
    it = it->next;
  }
}

DListNode *_create_node(int val) {
  DListNode *new_dlist_node = malloc(sizeof(DListNode));
  new_dlist_node->prev = NULL;
  new_dlist_node->next = NULL;
  new_dlist_node->val = val;
  return new_dlist_node;
}

DList *push_start(DList *self, int val) {
  DListNode *new_dlist_node = self->_create_node(val);
  if (self->length == 0) {
    self->head = new_dlist_node;
    self->tail = new_dlist_node;
    self->length++;
    return self;
  }
  DListNode *t = self->head;
  t->prev = new_dlist_node;
  new_dlist_node->next = t;
  self->head = new_dlist_node;
  self->length++;
  return self;
}

DList *push_tail(DList *self, int val) {
  DListNode *new_dlist_node = self->_create_node(val);
  if (self->length == 0) {
    self->head = new_dlist_node;
    self->tail = new_dlist_node;
    self->length++;
    return self;
  }
  DListNode *t = self->tail;
  new_dlist_node->prev = t;
  t->next = new_dlist_node;
  self->tail = new_dlist_node;
  self->length++;
  return self;
}

DList *push_index(DList *self, int val, int index) {
  DListNode *new_dlist_node = self->_create_node(val);
  DListNode *it = malloc(sizeof(DListNode));
  if (self->length < index) {
    printf("specified index is out of bounds!");
  } else if (index == 0) {
    self = self->push_start(self, val);
  } else if (self->length == index) {
    self = self->push_tail(self, val);
  }

  else if (index < self->length / 2) {
    it = self->head;
    for (int i = 1; i < index; i++) {
      it = it->next;
    }
    DListNode *t = it->next;
    new_dlist_node->next = t;
    t->prev = new_dlist_node;
    new_dlist_node->prev = it;
    it->next = new_dlist_node;
    self->length++;
  } else {
    it = self->tail;
    for (int i = self->length - 1; i > index; i--) {
      it = it->prev;
    }
    DListNode *t = it->prev;
    new_dlist_node->prev = t;
    t->next = new_dlist_node;
    new_dlist_node->next = it;
    it->prev = new_dlist_node;
    self->length++;
  }
  return self;
}

DList *delete_index(DList *self, int index) {
  DListNode *it = malloc(sizeof(DListNode));
  if (self->length < index) {
    printf("specified index is out of bounds!\n");
  } else if (index == 0) {
    self = self->delete_head(self);
  } else if (self->length == index) {
    self = self->delete_tail(self);
  } else if (index < self->length / 2) {
    it = self->head;
    for (int i = 0; i < index; i++) {
      it = it->next;
    }
    DListNode *p = it->prev;
    DListNode *n = it->next;
    p->next = n;
    n->prev = p;
    free(it);
    self->length--;
  } else {
    it = self->tail;
    for (int i = self->length; i > index; i--) {
      it = it->prev;
    }
    DListNode *n = it->next;
    DListNode *p = it->prev;
    n->prev = p;
    p->next = n;
    free(it);
    self->length--;
  }
  return self;
}

DList *delete_head(DList *self) {
  DListNode *t = self->head;
  t->next->prev = NULL;
  self->head = t->next;
  free(t);
  self->length--;
  return self;
}

DList *delete_tail(DList *self) {
  DListNode *t = self->tail;
  t->prev->next = NULL;
  self->tail = t->prev;
  free(t);
  self->length--;
  return self;
}

// "Constructor"

DList *new_dlist() {
  DList *new_list = malloc(sizeof(DList));
  new_list->length = 0;
  new_list->print = print_list;
  new_list->push_start = push_start;
  new_list->_create_node = _create_node;
  new_list->push_tail = push_tail;
  new_list->push_index = push_index;
  new_list->delete_head = delete_head;
  new_list->delete_tail = delete_tail;
  new_list->delete_index = delete_index;
  return new_list;
}

#endif