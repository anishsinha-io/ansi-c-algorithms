#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static void merge(int *a, int *l, int l_size, int *r, int r_size) {
  int i = 0, j = 0, k = 0;
  while (i < l_size && j < r_size) {
    if (l[i] < r[j]) {
      a[k] = l[i];
      i++;
    } else {
      a[k] = r[j];
      j++;
    }
    k++;
  }
  while (i < l_size) {
    a[k] = l[i];
    i++;
    k++;
  }
  while (j < r_size) {
    a[k] = r[j];
    j++;
    k++;
  }
}

void merge_sort(int *a, int l) {
  if (l < 2) {
    return;
  }
  int left_size = floor(l / 2);
  int right_size = l - left_size;
  int left_slice[left_size];
  int right_slice[right_size];
  for (int i = 0; i < left_size; i++) {
    left_slice[i] = a[i];
  }
  for (int j = left_size; j < l; j++) {
    right_slice[j] = a[j];
  }
  merge_sort(left_slice, left_size);
  merge_sort(right_slice, right_size);
  merge(a, left_slice, left_size, right_slice, right_size);
}