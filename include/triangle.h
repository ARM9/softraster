#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vectors.h"

typedef struct Tri_t {
    Vec4 v[3];
} Tri_t;

void fill_triangle(Tri_t *tri);

#endif //TRIANGLE_H

