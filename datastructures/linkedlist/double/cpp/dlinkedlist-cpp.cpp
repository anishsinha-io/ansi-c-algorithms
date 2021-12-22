#include "dlinkedlist-cpp.hpp"
#include <iostream>

int main() {
  DList<int> *list1 = new DList<int>();
  list1->add_to_tail(1);
  list1->add_to_tail(2);
  list1->add_to_head(0);
  list1->add_to_head(-1);
  // list1->add_index(8, 2);
  list1->print();
  return 0;
}