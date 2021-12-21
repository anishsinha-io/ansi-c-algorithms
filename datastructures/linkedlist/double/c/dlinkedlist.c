#include "dlinkedlist.h"
#include <stdio.h>

int main() {
  DList *list = new_dlist();
  list = list->push_start(list, 1);
  list = list->push_start(list, 0);
  list = list->push_start(list, -1);
  list = list->push_tail(list, 2);
  list = list->push_tail(list, 3);
  list = list->push_index(list, 8, 0);
  list = list->push_index(list, 12, 5);
  list = list->delete_index(list, 1);
  list = list->delete_index(list, 5);
  list->print(list);
  return 0;
}