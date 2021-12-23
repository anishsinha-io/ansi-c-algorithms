#include "clinkedlist.h"
#include <stdio.h>

int main() {
  CList *list1 = new_clist();
  list1 = list1->push_head(list1, 1);
  list1 = list1->push_head(list1, 2);
  list1 = list1->push_head(list1, 3);
  list1 = list1->push_tail(list1, 8);
  list1 = list1->push_index(list1, 9, 2);
  list1 = list1->push_index(list1, 4, 0);
  list1 = list1->push_index(list1, 12, 6);
  list1 = list1->delete_head(list1);
  list1 = list1->delete_tail(list1);
  list1->print(list1);
  printf("\nother side: %d\n", list1->length);
  return 0;
}
