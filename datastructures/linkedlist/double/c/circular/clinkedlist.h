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
  unsigned int (*get_length)(const struct CList *);
  CListNode *(*_create_node)(int val);

  // main methods

  struct CList *(*push_head)(struct CList *, int val);
  struct CList *(*push_tail)(struct CList *, int val);
  struct CList *(*push_index)(struct CList *, int val, int index);

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

CList *push_index(CList *self, int val, int index) {
  CListNode *new_node = self->_create_node(val);
  if (index > self->length) {
    printf("specified index %d out of range for list with length %d!", index,
           self->length);
  } else if (index == 0) {
    return self->push_head(self, val);
  } else if (index == self->length) {
    return self->push_tail(self, val);
  }

  else {
    CListNode *it = self->entry;
    for (int i = 0; i < index; i++) {
      it = it->next;
    }
    CListNode *p = it->prev;
    p->next = new_node;
    new_node->prev = p;
    new_node->next = it;
    it->prev = new_node;
  }
  self->length++;
  return self;
}

CList *delete_head(CList *self) {
  if (self->length == 0) {
    printf("cannot shift element from front of an empty list!");
    return self;

  } else if (self->length == 1) {
    self->length = 0;
    self->entry = NULL;
    free(self->entry);
    return self;
  }

  else {
    CListNode *p = self->entry->prev;
    CListNode *n = self->entry->next;
    p->next = n;
    n->prev = p;
    self->entry = n;
  }
  self->length--;
  return self;
}

CList *delete_tail(CList *self) {
  if (self->length == 0) {
    printf("cannot shift element from front of an empty list");
    return self;
  } else if (self->length == 1) {
    self->length = 0;
    self->entry = NULL;
    free(self->entry);
    return self;
  } else {
    CListNode *p = self->entry->prev->prev;
    CListNode *n = self->entry;
    free(self->entry->prev);
    n->prev = p;
    p->next = n;
  }
  self->length--;
  return self;
}

void print(const CList *self) {
  CListNode *it = self->entry;
  for (int i = 0; i < self->length; i++) {
    printf("%d ", it->val);
    it = it->next;
  }
}

unsigned int get_length(const CList *self) { return self->length; }

CList *new_clist() {
  CList *new_clist = malloc(sizeof(CList));
  new_clist->_create_node = _create_node;
  new_clist->length = 0;
  new_clist->push_head = push_head;
  new_clist->push_tail = push_tail;
  new_clist->push_index = push_index;
  new_clist->print = print;
  new_clist->get_length = get_length;
  new_clist->delete_head = delete_head;
  new_clist->delete_tail = delete_tail;
  return new_clist;
}
#endif