#include "btree.h"
#include "./mergesort.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Node *root = create_tree(a, 0, sizeof(a) / sizeof(int));
  Node *ins = insert_node(root, 11);
  Node *t = delete_node(root, 11);
  return 0;
}
