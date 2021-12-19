#include "./matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Matrix *multiply_matrices_naive(Matrix *A, Matrix *B) {
  Matrix *C = create_matrix(NULL, A->rows, B->cols);
  if (A->cols != B->rows) {
    printf("invalid_request");
    return NULL;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->cols; j++) {
      C->data[i][j] = 0;
      for (int k = 0; k < A->cols; k++) {
        C->data[i][j] += A->data[i][k] * B->data[k][j];
      }
    }
  }
  return C;
}

static Matrix *partition_matrix(Matrix *A, int n_rows, int n_cols,
                                int quadrant) {
  Matrix *P = create_matrix(NULL, n_rows, n_cols);
  if (quadrant == 1) {
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        P->data[i][j] = A->data[i][j];
      }
    }
  } else if (quadrant == 2) {
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        P->data[i][j] = A->data[i][n_cols + j];
      }
    }
  } else if (quadrant == 3) {
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        P->data[i][j] = A->data[n_rows + i][j];
      }
    }
  } else if (quadrant == 4) {
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        P->data[i][j] = A->data[i + n_rows][j + n_cols];
      }
    }
  } else {
    return NULL;
  }
  return P;
}

Matrix *square_matrix_multiply_recursive(Matrix *A, Matrix *B) {
  if (A->cols != B->cols && A->rows != B->rows) {
    printf("invalid_request");
    return NULL;
  }
  int size = A->rows;
  Matrix *C = create_matrix(NULL, size, size);
  if (size == 1) {
    C->data[0][0] = A->data[0][0] * B->data[0][0];
  } else {
    Matrix *A_q1 = partition_matrix(A, size / 2, size / 2, 1);
    Matrix *A_q2 = partition_matrix(A, size / 2, size / 2, 2);
    Matrix *A_q3 = partition_matrix(A, size / 2, size / 2, 3);
    Matrix *A_q4 = partition_matrix(A, size / 2, size / 2, 4);
    Matrix *B_q1 = partition_matrix(B, size / 2, size / 2, 1);
    Matrix *B_q2 = partition_matrix(B, size / 2, size / 2, 2);
    Matrix *B_q3 = partition_matrix(B, size / 2, size / 2, 3);
    Matrix *B_q4 = partition_matrix(B, size / 2, size / 2, 4);
    C->data[0][0] = square_matrix_multiply_recursive(A_q1, B_q1)->data[0][0] +
                    square_matrix_multiply_recursive(A_q2, B_q3)->data[0][0];
    C->data[0][1] = square_matrix_multiply_recursive(A_q1, B_q2)->data[0][0] +
                    square_matrix_multiply_recursive(A_q2, B_q4)->data[0][0];
    C->data[1][0] = square_matrix_multiply_recursive(A_q3, B_q1)->data[0][0] +
                    square_matrix_multiply_recursive(A_q4, B_q3)->data[0][0];
    C->data[1][1] = square_matrix_multiply_recursive(A_q3, B_q2)->data[0][0] +
                    square_matrix_multiply_recursive(A_q4, B_q4)->data[0][0];
  }
  return C;
}
