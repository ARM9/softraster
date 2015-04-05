#ifndef VECTORS_H
#define VECTORS_H

#include "numbers.h"

typedef struct Vec2 {
    fixed x, y;
} Vec2;

typedef struct Vec3 {
    fixed x, y, z;
} Vec3;

typedef struct Vec4 {
    fixed x, y, z, w;
} Vec4;

typedef struct Vec2f {
    float x, y;
} Vec2f;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct Vec4f {
    float x, y, z, w;
} Vec4f;

void vec2Set(Vec2 *v, fixed x, fixed y);
void vec2Add(Vec2 *a, Vec2 *b, Vec2 *c);
void vec2Sub(Vec2 *a, Vec2 *b, Vec2 *c);
void vec2Mul(Vec2 *a, Vec2 *b, Vec2 *c);
fixed vec2Dot(Vec2 *a, Vec2 *b);
fixed vec2Cross(Vec2 *a, Vec2 *b);

void vec3Set(Vec3 *v, fixed x, fixed y, fixed z);
void vec3Add(Vec3 *a, Vec3 *b, Vec3 *c);
void vec3Sub(Vec3 *a, Vec3 *b, Vec3 *c);
void vec3Mul(Vec3 *a, Vec3 *b, Vec3 *c);
fixed vec3Dot(Vec3 *a, Vec3 *b);
void vec3Cross(Vec3 *a, Vec3 *b, Vec3 *c);

void vec4Set(Vec4 *v, fixed x, fixed y, fixed z, fixed w);
void vec4Add(Vec4 *a, Vec4 *b, Vec4 *c);
void vec4Sub(Vec4 *a, Vec4 *b, Vec4 *c);
void vec4Mul(Vec4 *a, Vec4 *b, Vec4 *c);
fixed vec4Dot(Vec4 *a, Vec4 *b);

#endif  //VECTORS_H
