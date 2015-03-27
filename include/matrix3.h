#ifndef MATRIX3_H
#define MATRIX3_H

#include "numbers.h"

typedef struct Mat3 {
    fixed n11, n12, n13,
          n21, n22, n23,
          n31, n32, n33;
} Mat3;

void mat3Set(Mat3 *mat, fixed n11, fixed n12, fixed n13,
                        fixed n21, fixed n22, fixed n23,
                        fixed n31, fixed n32, fixed n33);
void mat3Copy(Mat3 *dest, Mat3 *src);
void mat3Identity(Mat3 *a);
fixed mat3Det(Mat3 *a);
void mat3Add(Mat3 *dest, Mat3 *a, Mat3 *b);
void mat3Sub(Mat3 *dest, Mat3 *a, Mat3 *b);
void mat3Mult(Mat3 *dest, Mat3 *a, Mat3 *b);
void mat3Rotate(Mat3 *dest, fixed angle);

#endif //MATRIX3_H
