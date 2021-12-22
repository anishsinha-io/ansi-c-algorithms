#include "clinkedlist.h"
#include <stdio.h>

int main() {
  CList *list1 = new_clist();
  list1 = list1->push_tail(list1, 1);
  printf("here\n");
  printf("%d\n", list1->tail->val);
  list1 = list1->push_tail(list1, 2);
  printf("%d\n", list1->tail->val);
  list1 = list1->push_tail(list1, 3);
  printf("%d\n", list1->tail->val);

  return 0;
}