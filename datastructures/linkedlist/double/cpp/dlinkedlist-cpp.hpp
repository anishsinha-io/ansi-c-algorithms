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
  T delete_head();
  T delete_tail();
  T delete_index(int);
  unsigned int length;

protected:
  DListNode<T> *head, *tail;
};

template <class T> void DList<T>::add_to_tail(const T &val) {
  if (tail != NULL) {
    tail = new DListNode<T>(val, 0, tail);
    tail->prev->next = tail;
    length++;
  } else {
    head = tail = new DListNode<T>(val);
    length++;
  }
}

template <class T> void DList<T>::add_to_head(const T &val) {
  DListNode<T> *new_node = new DListNode(val);
  DListNode<T> *t = head;
  new_node->next = t;
  t->prev = new_node;
  head = new_node;
  length++;
}

template <class T> void DList<T>::add_index(const T &val, int index) {
  DListNode<T> *new_node = new DListNode(val);
  if (index == 0) {
    return add_to_head(val);
  }
  if (index == length) {
    return add_to_tail(val);
  }
  if (index > length) {
    std::cout << "index " << index << " out of bounds!" << std::endl;
    return;
  }
  DListNode<T> *it = head;
  for (int i = 0; i < index; i++) {
    it = it->next;
  }
  DListNode<T> *p = it->prev;
  p->next = new_node;
  it->prev = new_node;
  new_node->prev = p;
  new_node->next = it;
  length++;
}

template <class T> T DList<T>::delete_head() {
  DListNode<T> *t = head;
  t->next->prev = NULL;
  head = t->next;
  T val = t->val;
  delete t;
  return val;
}

template <class T> T DList<T>::delete_tail() {
  DListNode<T> *t = tail;
  t->prev->next = NULL;
  tail = t->prev;
  T val = t->val;
  delete t;
  return val;
}

template <class T> T DList<T>::delete_index(int index) {
  if (index > length) {
    std::cout << "index " << index << " out of bounds!" << std::endl;
    return -1;
  }
  if (index == 0) {
    return delete_head();
  }
  if (index == length) {
    return delete_tail();
  }
  if (index < length / 2) {
    DListNode<T> *it = head;
    for (int i = 0; i < index; i++) {
      it = it->next;
    }
    DListNode<T> *p = it->prev;
    DListNode<T> *n = it->next;
    p->next = n;
    n->prev = p;
    T val = it->val;
    delete it;
    return val;
  }
  DListNode<T> *it = tail;
  for (int i = length; i > index + 1; i--) {
    it = it->prev;
  }
  DListNode<T> *p = it->prev;
  DListNode<T> *n = it->next;
  n->prev = p;
  p->next = n;
  T val = it->val;
  delete it;
  return val;
}

template <class T> void DList<T>::print() {
  DListNode<T> *it = head;
  while (it != NULL) {
    std::cout << it->val << std::endl;
    it = it->next;
  }
}

#endif