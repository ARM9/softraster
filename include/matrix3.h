#ifndef MATRIX3_H
#define MATRIX3_H

#include "numbers.h"

typedef struct mat3 {
    fixed n11, n12, n13,
          n21, n22, n23,
          n31, n32, n33;
} mat3;

void mat3Set(mat3 *mat, fixed n11, fixed n12, fixed n13,
                        fixed n21, fixed n22, fixed n23,
                        fixed n31, fixed n32, fixed n33);
void mat3Copy(mat3 *dest, mat3 *src);
void mat3Identity(mat3 *a);
fixed mat3Det(mat3 *a);
void mat3Add(mat3 *dest, mat3 *a, mat3 *b);
void mat3Sub(mat3 *dest, mat3 *a, mat3 *b);
void mat3Mult(mat3 *dest, mat3 *a, mat3 *b);
void mat3Rotate(mat3 *dest, fixed angle);

#endif //MATRIX3_H
