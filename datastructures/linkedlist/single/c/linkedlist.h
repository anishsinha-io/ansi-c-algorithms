#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _LINKED_LIST
#define _LINKED_LIST

typedef struct ListNode {
  void *data;
  struct ListNode *next;
} ListNode;

ListNode *create_list_node(void *data, size_t data_size) {
  ListNode *new_node = malloc(sizeof(ListNode));
  new_node->data = malloc(sizeof(data_size));
  new_node->next = NULL;
  for (int i = 0; i < data_size; i++) {
    *(char *)(new_node->data + i) = *(char *)(data + i);
  }
  return new_node;
}

// does not work with generic args
int is_in_list(ListNode *head, int data) {
  ListNode *it = head;
  int i;
  while (it != NULL) {
    if (*(int *)it->data == data) {
      return i;
      break;
    }
    it = it->next;
  }
  return -1;
}

ListNode *push_start(ListNode *head, void *data, size_t data_size) {
  if (head == NULL) {
    printf("here");
    head = create_list_node(data, data_size);
  }
  ListNode *new_node = create_list_node(data, data_size);
  ListNode *t = head;
  new_node->next = t;
  head = new_node;
  return head;
}

ListNode *push_end(ListNode *head, void *data, size_t data_size) {
  ListNode *new_node = create_list_node(data, data_size);
  ListNode *t = head;
  while (t->next != NULL) {
    t = t->next->next;
  }
  t->next = new_node;
  return head;
}

ListNode *push_index(ListNode *head, void *data, size_t data_size, int index) {
  ListNode *new_node = create_list_node(data, data_size);
  ListNode *it = head;
  if (index == 0) {
    head = push_start(head, data, data_size);
    return head;
  }
  for (int i = 1; i < index; i++) {
    if (it->next == NULL) {
      printf("insertion failed. list not long enough to insert at index %d\n",
             index);
      return head;
    }
    it = it->next;
  }
  new_node->next = it->next;
  it->next = new_node;
  return head;
}

ListNode *delete_index(ListNode *head, int index) {
  ListNode *it = head;
  for (int i = 1; i < index; i++) {
    if (it->next == NULL) {
      printf("deletion failed. list not long enough to delete at index %d\n",
             index);
      return head;
    }
    it = it->next;
  }
  ListNode *new_next = it->next->next;
  it->next = NULL;
  free(it->next);
  it->next = new_next;
  return head;
}

ListNode *delete_head(ListNode *head) {
  ListNode *t = head;
  head = t->next;
  free(t);
  return head;
}

ListNode *delete_end(ListNode *head) {
  ListNode *it1 = head;
  ListNode *it2 = head;
  while (it1->next != NULL) {
    it2 = it1->next;
    it1 = it1->next->next;
  }
  it2->next = NULL;
  it1 = NULL;
  free(it1);
  return head;
}

void print_linked_list(ListNode *head) {
  ListNode *it = head;
  while (it != NULL) {
    printf("%d\n", *(int *)it->data);
    it = it->next;
  }
}

#endif