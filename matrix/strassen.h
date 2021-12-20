#ifndef _STRASSEN
#define _STRASSEN

#include "matrix.h"
#include "util.h"

Matrix *strassen(Matrix *, Matrix *, Matrix *, unsigned int);
static void strassen_r(Matrix *, Matrix *, Matrix *, int);
static void sum(Matrix *, Matrix *, Matrix *, int);
static void subtract(Matrix *, Matrix *, Matrix *, int);

static void strassen_r(Matrix *A, Matrix *B, Matrix *C, int tam) {
  if (tam == 1) {
    C->data[0][0] = A->data[0][0] * B->data[0][0];
  } else {
    unsigned int new_tam = tam / 2;
    Matrix *a11 = create_empty_matrix(new_tam, new_tam);
    Matrix *a12 = create_empty_matrix(new_tam, new_tam);
    Matrix *a21 = create_empty_matrix(new_tam, new_tam);
    Matrix *a22 = create_empty_matrix(new_tam, new_tam);

    Matrix *b11 = create_empty_matrix(new_tam, new_tam);
    Matrix *b12 = create_empty_matrix(new_tam, new_tam);
    Matrix *b21 = create_empty_matrix(new_tam, new_tam);
    Matrix *b22 = create_empty_matrix(new_tam, new_tam);

    Matrix *c11 = create_empty_matrix(new_tam, new_tam);
    Matrix *c12 = create_empty_matrix(new_tam, new_tam);
    Matrix *c21 = create_empty_matrix(new_tam, new_tam);
    Matrix *c22 = create_empty_matrix(new_tam, new_tam);

    Matrix *p1 = create_empty_matrix(new_tam, new_tam);
    Matrix *p2 = create_empty_matrix(new_tam, new_tam);
    Matrix *p3 = create_empty_matrix(new_tam, new_tam);
    Matrix *p4 = create_empty_matrix(new_tam, new_tam);
    Matrix *p5 = create_empty_matrix(new_tam, new_tam);
    Matrix *p6 = create_empty_matrix(new_tam, new_tam);
    Matrix *p7 = create_empty_matrix(new_tam, new_tam);

    Matrix *a_result = create_empty_matrix(new_tam, new_tam);
    Matrix *b_result = create_empty_matrix(new_tam, new_tam);

    unsigned int i, j;

    for (i = 0; i < new_tam; i++) {
      for (j = 0; j < new_tam; j++) {
        a11->data[i][j] = A->data[i][j];
        a12->data[i][j] = A->data[i][j + new_tam];
        a21->data[i][j] = A->data[i + new_tam][j];
        a22->data[i][j] = A->data[i + new_tam][j + new_tam];

        b11->data[i][j] = B->data[i][j];
        b12->data[i][j] = B->data[i][j + new_tam];
        b21->data[i][j] = B->data[i + new_tam][j];
        b22->data[i][j] = B->data[i + new_tam][j + new_tam];
      }
    }

    sum(a11, a22, a_result, new_tam);
    sum(b11, b22, b_result, new_tam);
    strassen_r(a_result, b_result, p1, new_tam);

    sum(a21, a22, a_result, new_tam);
    strassen_r(a_result, b11, p2, new_tam);

    subtract(b12, b22, b_result, new_tam);
    strassen_r(a11, b_result, p3, new_tam);

    subtract(b21, b11, b_result, new_tam);
    strassen_r(a22, b_result, p4, new_tam);

    sum(a11, a12, a_result, new_tam);
    strassen_r(a_result, b22, p5, new_tam);

    subtract(a21, a11, a_result, new_tam);
    sum(b11, b12, b_result, new_tam);
    strassen_r(a_result, b_result, p6, new_tam);

    subtract(a12, a22, a_result, new_tam);
    sum(b21, b22, b_result, new_tam);
    strassen_r(a_result, b_result, p7, new_tam);

    sum(p3, p5, c12, new_tam);
    sum(p2, p4, c21, new_tam);

    sum(p1, p4, a_result, new_tam);
    sum(a_result, p7, b_result, new_tam);
    subtract(b_result, p5, c11, new_tam);

    sum(p1, p3, a_result, new_tam);
    sum(a_result, p6, b_result, new_tam);
    subtract(b_result, p2, c22, new_tam);

    for (i = 0; i < new_tam; i++) {
      for (j = 0; j < new_tam; j++) {
        C->data[i][j] = c11->data[i][j];
        C->data[i][j + new_tam] = c12->data[i][j];
        C->data[i + new_tam][j] = c21->data[i][j];
        C->data[i + new_tam][j + new_tam] = c22->data[i][j];
      }
    }
  }
  return;
}

static void sum(Matrix *A, Matrix *B, Matrix *C, int tam) {
  unsigned int i, j;
  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      C->data[i][j] = A->data[i][j] + B->data[i][j];
    }
  }
}

static void subtract(Matrix *A, Matrix *B, Matrix *C, int tam) {
  unsigned int i, j;
  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      C->data[i][j] = A->data[i][j] - B->data[i][j];
    }
  }
}

Matrix *strassen(Matrix *A, Matrix *B, Matrix *C, unsigned int n) {
  unsigned int m = next_power_of_two(n);
  Matrix *a_prep = create_empty_matrix(m, m);
  Matrix *b_prep = create_empty_matrix(m, m);
  Matrix *c_prep = create_empty_matrix(m, m);

  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      a_prep->data[i][j] = A->data[i][j];
      b_prep->data[i][j] = B->data[i][j];
    }
  }
  strassen_r(a_prep, b_prep, c_prep, m);
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      C->data[i][j] = c_prep->data[i][j];
    }
  }
  return C;
}

#endif