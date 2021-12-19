#ifndef _UTIL
#define _UTIL

unsigned int next_power_of_two(unsigned int v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

#endif

// double P =
//     (A->data[0][0] + A->data[1][1]) * (B->data[0][0] + B->data[1][1]);
// double Q = (A->data[1][0] + A->data[1][1]) * B->data[0][0];
// double R = A->data[0][0] * (B->data[0][1] - B->data[1][1]);
// double S = A->data[1][1] * (B->data[1][0] - B->data[0][0]);
// double T = (A->data[0][0] + A->data[0][1]) * B->data[1][1];
// double U =
//     (A->data[1][0] - A->data[0][0]) * (B->data[0][0] + B->data[0][1]);
// double V =
//     (A->data[0][1] - A->data[1][1]) * (B->data[1][0] + B->data[1][1]);
// C->data[0][0] = P + S - T + V;
// C->data[0][1] = R + T;
// C->data[1][0] = Q + S;
// C->data[1][1] = P + R - Q + U;
// printf(
//     "\n-------------------------------------------------------------------"
//     "------------------------------------\n");
// print_matrix(C);
// printf(
//     "\n-------------------------------------------------------------------"
//     "------------------------------------\n");

//  Matrix *first_quadrant = msub(madd(T, S), madd(Q, U));
//     Matrix *second_quadrant = madd(P, Q);
//     Matrix *third_quadrant = madd(R, S);
//     Matrix *fourth_quadrant = msub(madd(T, P), msub(R, V));

//     C = copy_quadrant_into_matrix(first_quadrant, C, 1);
//     C = copy_quadrant_into_matrix(second_quadrant, C, 2);
//     C = copy_quadrant_into_matrix(third_quadrant, C, 3);
//     C = copy_quadrant_into_matrix(fourth_quadrant, C, 4);
//     printf("-------------------------------------------------------------------"
//            "------------------\n");
//     print_matrix(C);

// C->data[0][0] =
//         S->data[0][0] + T->data[0][0] + U->data[0][0] - Q->data[0][0];
//     C->data[0][1] = P->data[0][0] + Q->data[0][0];
//     C->data[1][0] = R->data[0][0] + S->data[0][0];
//     C->data[1][1] =
//         P->data[0][0] + T->data[0][0] - R->data[0][0] - V->data[0][0];