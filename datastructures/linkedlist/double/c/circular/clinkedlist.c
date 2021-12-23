#include "clinkedlist.h"
#include <stdio.h>

int main() {
  CList *list1 = new_clist();
  list1 = list1->push_head(list1, 1);
  list1 = list1->push_head(list1, 2);
  list1 = list1->push_head(list1, 3);
  printf("%d\n", list1->entry->prev->val);
  return 0;
}
