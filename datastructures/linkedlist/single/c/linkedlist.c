#include "linkedlist.h"
#include <stdio.h>

int main() {
  int point1 = 1;
  int point2 = 2;
  int point3 = 3;
  int point4 = 4;
  int point5 = 8;
  ListNode *head = create_list_node(&point1, sizeof(int));
  head = push_start(head, &point2, sizeof(int));
  head = push_start(head, &point3, sizeof(int));
  head = push_end(head, &point4, sizeof(int));
  head = push_index(head, &point5, sizeof(int), 0);
  head = delete_index(head, 2);
  head = delete_head(head);
  head = delete_end(head);
  int index = is_in_list(head, 3);
  printf("%d\n", index);
  return 0;
}