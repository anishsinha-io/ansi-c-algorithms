#ifndef _LINKED_LIST
#define _LINKED_LIST

typedef struct ListNode {
  void *data;
  ListNode *left;
} ListNode;

void push_start(ListNode **head, void *new_data, size_t data_size) {}

#endif