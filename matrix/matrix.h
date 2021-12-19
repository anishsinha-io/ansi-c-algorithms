#include "strassen.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _MATRIX
#define _MATRIX

typedef struct Matrix {
  unsigned int rows;
  unsigned int cols;
  double **data;
} Matrix;

static Matrix *construct_matrix(int n_rows, int n_cols) {
  Matrix *matrix = malloc(sizeof(Matrix));
  matrix->rows = n_rows;
  matrix->cols = n_cols;
  double **data = malloc(sizeof(double *) * n_rows);
  for (int i = 0; i < n_rows; i++) {
    data[i] = calloc(n_cols, sizeof(double));
  }
  matrix->data = data;
  return matrix;
}

Matrix *create_matrix(double *data, int n_rows, int n_cols) {
  Matrix *matrix = construct_matrix(n_rows, n_cols);
  for (size_t row = 0; row < n_rows; row++) {
    double *row_start = &data[row * n_cols];
    for (size_t col = 0; col < n_cols; col++) {
      matrix->data[row][col] = row_start[col];
    }
  }
  return matrix;
}

Matrix *create_empty_matrix(int n_rows, int n_cols) {
  Matrix *matrix = construct_matrix(n_rows, n_cols);
  return matrix;
}

bool match_dim(Matrix *A, Matrix *B) {
  if (A->rows != B->rows || A->cols != B->cols) {
    return false;
  }
  return true;
}

unsigned int get_largest_dimension(Matrix *A) {
  if (A->rows > A->cols) {
    return A->rows;
  }
  return A->cols;
}

Matrix *madd(Matrix *A, Matrix *B) {
  int c_dim = A->rows;
  Matrix *C = create_empty_matrix(c_dim, c_dim);
  if (!match_dim(A, B)) {
    printf("invalid_request");
    return NULL;
  }
  for (int i = 0; i < c_dim; i++) {
    for (int j = 0; j < c_dim; j++) {
      C->data[i][j] = A->data[i][j] + B->data[i][j];
    }
  }
  return C;
}

Matrix *msub(Matrix *A, Matrix *B) {
  int c_dim = A->rows;
  Matrix *C = create_empty_matrix(c_dim, c_dim);
  if (!match_dim(A, B)) {
    printf("invalid_request");
    return NULL;
  }
  for (int i = 0; i < c_dim; i++) {
    for (int j = 0; j < c_dim; j++) {
      C->data[i][j] = A->data[i][j] - B->data[i][j];
    }
  }
  return C;
}

Matrix *partition_matrix(Matrix *M, int quadrant) {
  Matrix *T = create_empty_matrix(M->rows / 2, M->cols / 2);
  if (quadrant == 1) {
    for (int i = 0; i < M->rows / 2; i++) {
      for (int j = 0; j < M->cols / 2; j++) {
        T->data[i][j] = M->data[i][j];
      }
    }
  } else if (quadrant == 2) {
    for (int i = 0; i < M->rows / 2; i++) {
      for (int j = M->cols / 2; j < M->cols; j++) {
        T->data[i][j - M->cols / 2] = M->data[i][j];
      }
    }
  } else if (quadrant == 3) {
    for (int i = M->rows / 2; i < M->rows; i++) {
      for (int j = 0; j < M->cols / 2; j++) {
        T->data[i - M->rows / 2][j] = M->data[i][j];
      }
    }
  } else if (quadrant == 4) {
    for (int i = M->rows / 2; i < M->rows; i++) {
      for (int j = M->cols / 2; j < M->cols; j++) {
        T->data[i - M->rows / 2][j - M->cols / 2] = M->data[i][j];
      }
    }
  } else {
    return NULL;
  }
  return T;
}

Matrix *resize_matrix(Matrix *M, int n_rows, int n_cols) {
  Matrix *T = create_empty_matrix(n_rows, n_cols);
  for (int i = 0; i < M->rows; i++) {
    for (int j = 0; j < M->cols; j++) {
      T->data[i][j] = M->data[i][j];
    }
  }
  return T;
}

Matrix *copy_quadrant_into_matrix(Matrix *A, Matrix *T, int quadrant) {
  if (T->rows != 2 * A->rows && T->cols != 2 * T->cols) {
    printf("invalid_request");
  }
  if (quadrant == 1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->cols; j++) {
        T->data[i][j] = A->data[i][j];
      }
    }
  } else if (quadrant == 2) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->cols; j++) {
        T->data[i][j + A->cols] = A->data[i][j];
      }
    }
  } else if (quadrant == 3) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->cols; j++) {
        T->data[i + A->rows][j] = A->data[i][j];
      }
    }
  } else if (quadrant == 4) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->rows; j++) {
        T->data[i + A->rows][j + A->cols] = A->data[i][j];
      }
    }
  } else {
    printf("invalid_request");
    return NULL;
  }
  return T;
}

void print_matrix(Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    printf("%s", "\n");
    for (int j = 0; j < m->cols; j++) {
      printf("%f\t", m->data[i][j]);
    }
  }
}

#endif