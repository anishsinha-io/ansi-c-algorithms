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
  void push_index(const T &, int);

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

template <class T> void CList<T>::push_index(const T &val, int index) {
  CListNode<T> *new_node = new CListNode(val);
  if (index > length) {
    std::cout << "index greater than list length!" << std::endl;
    return;
  } else if (index == 0) {
    return push_head(val);
  } else if (index == length) {
    return push_tail(val);
  } else {
    CListNode<T> *it = entry;
    for (int i = 0; i < index; i++) {
      it = it->next;
    }
    CListNode<T> *p = it->prev;
    p->next = new_node;
    new_node->prev = p;
    new_node->next = it;
    it->prev = new_node;
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

template <class T> T CList<T>::delete_head() {
  if (length == 0) {
    std::cout << "cannot shift from front of empty list!" << std::endl;
    return -1;
  } else if (length == 1) {
    length = 0;
    T val = entry->val;
    entry = NULL;
    delete entry;
    return val;
  } else {
    T val = entry->val;
    CListNode<T> *p = entry->prev;
    CListNode<T> *n = entry->next;
    p->next = n;
    n->prev = p;
    entry = n;
    length--;
    return val;
  }
}

template <class T> T CList<T>::delete_tail() {
  if (length == 0) {
    std::cout << "cannot pop from end of empty list!" << std::endl;
    return -1;
  } else if (length == 1) {
    length = 0;
    T val = entry->val;
    entry = NULL;
    delete entry;
    return val;
  } else {
    T val = entry->prev->val;
    CListNode<T> *p = entry->prev->prev;
    delete entry->prev;
    p->next = entry;
    entry->prev = p;
    length--;
    return val;
  }
}

template <class T> T CList<T>::delete_index(unsigned int index) {
  if (index > length) {
    std::cout << "specified index is out of bounds of list!" << std::endl;
    return -1;
  } else {
    CListNode<T> *it = entry;
    for (unsigned int i = 0; i < index; i++) {
      it = it->next;
    }
    CListNode<T> *p = it->prev;
    CListNode<T> *n = it->next;
    T val = it->val;
    p->next = n;
    n->prev = p;
    length--;
    delete it;
    return val;
  }
}

template <class T> CListNode<T> *CList<T>::get_entry() { return entry; }

#endif