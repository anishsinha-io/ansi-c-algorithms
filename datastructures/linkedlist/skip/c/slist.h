#include "models.h"
#include "slist-util.h"
#include <math.h>

#ifndef _SLIST
#define _SLIST

SListNode *_create_sentinel(unsigned int level, SIGN sign) {
  SListNode *new_sentinel = malloc(sizeof(SListNode));
  if (sign == positive) {
    new_sentinel->val = INFINITY;
  } else {
    new_sentinel->val = -INFINITY;
  }
  new_sentinel->level = level;
  new_sentinel->bottom = new_sentinel->top = new_sentinel->next =
      new_sentinel->prev = NULL;
  new_sentinel->is_sentinel = true;
  return new_sentinel;
}

SListNode *_create_node(double val, unsigned int level) {
  SListNode *new_node = malloc(sizeof(SListNode));
  new_node->val = val;
  new_node->bottom = new_node->top = new_node->next = new_node->prev = NULL;
  new_node->is_sentinel = false;
  new_node->level = level;
  return new_node;
}

SList *new_slist() {
  SList *new_slist = malloc(sizeof(SList));
  new_slist->_create_sentinel = _create_sentinel;
  new_slist->left_sentinel = new_slist->_create_sentinel(0, negative);
  new_slist->right_sentinel = new_slist->_create_sentinel(0, positive);
  new_slist->left_sentinel->next = new_slist->right_sentinel;
  new_slist->right_sentinel->prev = new_slist->left_sentinel;
  new_slist->length = 0;
  new_slist->max_levels = 1;
  new_slist->head = new_slist->tail = NULL;
  new_slist->util = new_slist_util();
  return new_slist;
}

#endif