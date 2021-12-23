#include <iostream>

#ifndef _CLINKEDLIST_DOUBLE_CPP
#define _CLINKEDLIST_DOUBLE_CPP

template <class T> class CListNode {
public:
  CListNode() {
    val = 0;
    next = prev = NULL;
  }
  CListNode(const T &v, CListNode *p = NULL, CListNode *n = NULL) {
    val = v;
    prev = p;
    next = n;
  }
  T val;
  CListNode *next, *prev;
};

template <class T> class CList {
public:
  CList() { entry = NULL; }
  unsigned int length;
  void print();
  void push_head(const T &);
  void push_tail(const T &);
  void push_index(const T &);

  T delete_head();
  T delete_tail();
  T delete_index(unsigned int);
  CListNode<T> *get_entry();

protected:
  CListNode<T> *entry;
};

template <class T> void CList<T>::push_head(const T &val) {
  CListNode<T> *new_node = new CListNode(val);
  if (length == 0) {
    entry = new_node;
    new_node->prev = entry;
    new_node->next = entry;
  } else {
    CListNode<T> *t = entry;
    new_node->next = entry;
    new_node->prev = entry->prev;
    t->prev->next = new_node;
    t->prev = new_node;
    entry = new_node;
  }
  length++;
}

template <class T> void CList<T>::push_tail(const T &val) {
  CListNode<T> *new_node = new CListNode(val);
  if (length == 0) {
    entry = new_node;
    new_node->prev = entry;
    new_node->next = entry;
  } else {
    CListNode<T> *t = entry;
    new_node->next = entry;
    new_node->prev = entry->prev;
    entry->prev->next = new_node;
    entry->prev = new_node;
  }
  length++;
}

template <class T> void CList<T>::print() {
  CListNode<T> *it = entry;
  for (int i = 0; i < length; i++) {
    std::cout << it->val << ", " << std::flush;
    it = it->next;
  }
}

template <class T> CListNode<T> *CList<T>::get_entry() { return entry; }

#endif