#ifndef MATRIX2_H
#define MATRIX2_H

#include "numbers.h"

typedef struct mat2 {
    fixed n11, n12,
          n21, n22;
} mat2;

void mat2Set(mat2 *mat, fixed n11, fixed n12, fixed n21, fixed n22);
void mat2Copy(mat2 *dest, mat2 *src);
void mat2Identity(mat2 *a);
fixed mat2Det(mat2 *a);
void mat2Add(mat2 *dest, mat2 *a, mat2 *b);
void mat2Sub(mat2 *dest, mat2 *a, mat2 *b);
void mat2Mult(mat2 *dest, mat2 *a, mat2 *b);
void mat2Rotate(mat2 *dest, fixed angle);

#endif //MATRIX2_H
