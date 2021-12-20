#ifndef _DLINKED_LIST
#define _DLINKED_LIST

typedef struct DListNode {
  void *data;
  struct DListNode *prev;
  struct DListNode *next;
} DListNode;

DListNode *create_dlist_node(void *data, size_t data_size) {
  DListNode *new_node = malloc(sizeof(DListNode));
  new_node->data = malloc(sizeof(data_size));
  new_node->prev = NULL;
  new_node->next = NULL;
  for (int i = 0; i < data_size; i++) {
    *(char *)(new_node->data + i) = *(char *)(data + i);
  }
  return new_node;
}

DListNode *push_start(DListNode *head, void *data, size_t data_size) {
  DListNode *new_node = create_dlist_node(data, data_size);
  new_node->next = head;
  DListNode *t = head;
  new_node->next = t;
  head = new_node;
  return head;
}

DListNode *push_end(DListNode *head, void *data, size_t data_size) {
  DListNode *new_node = create_dlist_node(data, data_size);
  DListNode *t = head;
  while (t->next != NULL) {
    t->next = t->next->next;
  }
  t->next = new_node;
  return head;
}

DListNode *push_index(DListNode *head, void *data, size_t data_size,
                      unsigned int index) {
  DListNode *new_node = create_dlist_node(data, data_size);
  DListNode *it = head;
  for (int i = 1; i < index; i++) {
    it = it->next;
  }
  DListNode *t = it->next;
  it->next = new_node;
  new_node->prev = it;
  new_node->next = t;
  return head;
}

DListNode *delete_index(DListNode *head, unsigned int index) {}
#endif