#ifndef VECTORS_H
#define VECTORS_H

#include "numbers.h"

typedef struct vec2 {
    fixed x, y;
} vec2;

typedef struct vec3 {
    fixed x, y, z;
} vec3;

typedef struct vec4 {
    fixed x, y, z, w;
} vec4;

void vec2Set(vec2 *v, fixed x, fixed y);
void vec2Add(vec2 *a, vec2 *b, vec2 *c);
void vec2Sub(vec2 *a, vec2 *b, vec2 *c);
void vec2Mul(vec2 *a, vec2 *b, vec2 *c);
fixed vec2Dot(vec2 *a, vec2 *b);

void vec3Set(vec3 *v, fixed x, fixed y, fixed z);
void vec3Add(vec3 *a, vec3 *b, vec3 *c);
void vec3Sub(vec3 *a, vec3 *b, vec3 *c);
void vec3Mul(vec3 *a, vec3 *b, vec3 *c);
fixed vec3Dot(vec3 *a, vec3 *b);
void vec3Cross(vec3 *a, vec3 *b, vec3 *c);

void vec4Set(vec4 *v, fixed x, fixed y, fixed z, fixed w);
void vec4Add(vec4 *a, vec4 *b, vec4 *c);
void vec4Sub(vec4 *a, vec4 *b, vec4 *c);
void vec4Mul(vec4 *a, vec4 *b, vec4 *c);
fixed vec4Dot(vec4 *a, vec4 *b);

#endif  //VECTORS_H
