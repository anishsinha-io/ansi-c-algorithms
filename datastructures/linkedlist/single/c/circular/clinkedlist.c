#include "clinkedlist.h"
#include <stdio.h>

int main() {
  CList *list1 = new_clist();
  list1->push_head(list1, 1);
  printf("%d\n", list1->head->val);
  return 0;
}