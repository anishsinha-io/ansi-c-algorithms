#include "clinkedlist-cpp.hpp"
#include <iostream>

int main() {
  CList<int> *list1 = new CList<int>();
  list1->push_head(4);
  list1->push_head(3);
  list1->push_head(2);
  list1->push_head(1);
  list1->push_tail(5);
  list1->push_index(8, 2);
  list1->push_index(9, 2);
  list1->delete_tail();
  list1->delete_index(3);
  list1->print();
  return 0;
}