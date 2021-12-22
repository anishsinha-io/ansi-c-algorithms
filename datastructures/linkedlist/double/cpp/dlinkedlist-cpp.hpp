#include <iostream>
#include <string>

#ifndef _DLINKEDLIST_CPP
#define _DLINKEDLIST_CPP

template <class T> class DListNode {
public:
  DListNode() {
    val = 0;
    next = prev = NULL;
  }
  DListNode(const T &el, DListNode *n = NULL, DListNode *p = NULL) {
    val = el;
    next = n;
    prev = p;
  }
  T val;
  DListNode *next, *prev;
};

template <class T> class DList {
public:
  DList() { head = tail = NULL; }
  void print();
  void add_to_tail(const T &);
  void add_to_head(const T &);
  void add_index(const T &, int);
  T delete_tail();
  unsigned int length;

protected:
  DListNode<T> *head, *tail;
};

template <class T> void DList<T>::add_to_tail(const T &val) {
  if (tail != NULL) {
    tail = new DListNode<T>(val, 0, tail);
    tail->prev->next = tail;
  } else {
    head = tail = new DListNode<T>(val);
  }
}

template <class T> void DList<T>::add_to_head(const T &val) {
  DListNode<T> *new_node = new DListNode(val);
  DListNode<T> *t = head;
  new_node->next = t;
  t->prev = new_node;
  head = new_node;
}

template <class T> void DList<T>::add_index(const T &val, int index) {
  DListNode<T> *new_node = new DListNode(val);
  DListNode<T> *it = head;
  for (int i = 0; i < index; i++) {
    it = it->next;
  }
  DListNode<T> *p = it->prev;
  p->next = new_node;
  it->prev = new_node;
  new_node->prev = p;
  new_node->next = it;
}

template <class T> void DList<T>::print() {
  DListNode<T> *it = head;
  while (it != NULL) {
    std::cout << it->val << std::endl;
    it = it->next;
  }
}

#endif