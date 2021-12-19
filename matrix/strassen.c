#include "strassen.h"
#include "matrix.h"

int main() {
  double matrix_one_data[5][5] = {{1, 4, 6, -7, -8},
                                  {9, 4, 3, 9, 7},
                                  {4, 8, 2, 2, -4},
                                  {1, 3, 5, 5, -6},
                                  {-3, 3, 7, 5, 3}};
  double matrix_two_data[5][5] = {{14, 2, -1, 5, 12},
                                  {3, 7, -8, 9, -3},
                                  {4, 4, 6, -2, -9},
                                  {15, 6, 6, -7, 3},
                                  {1, 2, 9, 5, 6}};
  unsigned int n = 5;
  Matrix *matrix_one = create_matrix((double *)matrix_one_data, 5, 5);
  Matrix *matrix_two = create_matrix((double *)matrix_two_data, 5, 5);
  Matrix *matrix_three = create_empty_matrix(5, 5);
  Matrix *m4 = strassen(matrix_one, matrix_two, matrix_three, n);
  print_matrix(m4);
  return 0;
}