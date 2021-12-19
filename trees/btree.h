#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *left;
  struct Node *right;
} Node;

Node *create_node(int val) {
  Node *newNode = (Node *)(malloc(sizeof(Node)));
  newNode->val = val;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *create_tree(int *buffer, int low, int high) {
  if (low > high) {
    return NULL;
  }
  int mid = (low + high) / 2;
  Node *root = create_node(buffer[mid]);
  root->left = create_tree(buffer, low, mid - 1);
  root->right = create_tree(buffer, mid + 1, high);
  return root;
}

bool search_tree(Node *root, int val) {
  if (root == NULL) {
    return false;
  } else if (val == root->val) {
    return true;
  } else if (val < root->val) {
    return search_tree(root->left, val);
  } else {
    return search_tree(root->right, val);
  }
}

Node *invert_tree(Node *root) {
  if (root == NULL) {
    return root;
  }
  Node *t = root->right;
  root->right = root->left;
  root->left = t;
  invert_tree(root->left);
  invert_tree(root->right);
  return root;
}

Node *insert_node(Node *root, int val) {
  Node *new_node = create_node(val);
  if (root == NULL) {
    return new_node;
  } else if (root->val < val) {
    root->right = insert_node(root->right, val);
  } else {
    root->left = insert_node(root->left, val);
  }
  return new_node;
}

Node *find_min(Node *root) {
  Node *t = root;
  while (t->left != NULL) {
    t = t->left;
  }
  return t;
}

Node *delete_node(Node *root, int val) {
  if (root == NULL) {
    return NULL;
  } else if (root->val < val) {
    root->right = delete_node(root->right, val);
  } else if (root->val > val) {
    root->left = delete_node(root->left, val);
  } else {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
      return root;
    } else if (root->left == NULL) {
      Node *t = root;
      root = root->right;
      free(t);
    } else if (root->right == NULL) {
      Node *t = root;
      root = root->left;
      free(t);
    } else {
      Node *t = find_min(root->right);
      root->val = t->val;
      root->right = delete_node(root->right, t->val);
    }
  }
  return root;
}
