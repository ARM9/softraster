#include "precompiled.h"
#include "numbers.h"
#include "vectors.h"

/* 2D Vectors ************************/
inline void vec2Set(Vec2 *v, fixed x, fixed y){
    v->x = x;
    v->y = y;
}

inline void vec2Add(Vec2 *a, Vec2 *b, Vec2 *c){
    a->x = b->x + c->x;
    a->y = b->y + c->y;
}

inline void vec2Sub(Vec2 *a, Vec2 *b, Vec2 *c){
    a->x = b->x - c->x;
    a->y = b->y - c->y;
}

inline void vec2Mul(Vec2 *a, Vec2 *b, Vec2 *c){
    a->x = fixmul(b->x, c->x);
    a->y = fixmul(b->y, c->y);
}

inline fixed vec2Dot(Vec2 *a, Vec2 *b){
    return fixmul(a->x, b->x) + fixmul(a->y, b->y);
}

inline fixed vec2Cross(Vec2 *a, Vec2 *b){
    return fixmul(a->x, b->y) - fixmul(a->y, b->x);
}

/* 3D Vectors ************************/
inline void vec3Set(Vec3 *v, fixed x, fixed y, fixed z){
    v->x = x;
    v->y = y;
    v->z = z;
}

inline void vec3Add(Vec3 *a, Vec3 *b, Vec3 *c){
    a->x = b->x + c->x;
    a->y = b->y + c->y;
    a->z = b->z + c->z;
}

inline void vec3Sub(Vec3 *a, Vec3 *b, Vec3 *c){
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;
}

inline void vec3Mul(Vec3 *a, Vec3 *b, Vec3 *c){
    a->x = fixmul(b->x, c->x);
    a->y = fixmul(b->y, c->y);
    a->z = fixmul(b->z, c->z);
}

inline fixed vec3Dot(Vec3 *a, Vec3 *b){
    return fixmul(a->x, b->x) + fixmul(a->y, b->y) + fixmul(a->z, b->z);
}

inline void vec3Cross(Vec3 *a, Vec3 *b, Vec3 *c){
    Vec3 t;
    t.x = fixmul(b->y, c->z) - fixmul(b->z, c->y);
    t.y = fixmul(b->z, c->x) - fixmul(b->x, c->z);
    t.z = fixmul(b->x, c->y) - fixmul(b->y, c->x);
    vec3Set(a, t.x, t.y, t.z);
}

/* 4D Vectors ************************/
inline void vec4Set(Vec4 *v, fixed x, fixed y, fixed z, fixed w){
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

inline void vec4Add(Vec4 *a, Vec4 *b, Vec4 *c){
    a->x = b->x + c->x;
    a->y = b->y + c->y;
    a->z = b->z + c->z;
    a->w = b->w + c->w;
}

inline void vec4Sub(Vec4 *a, Vec4 *b, Vec4 *c){
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;
    a->w = b->w - c->w;
}

inline void vec4Mul(Vec4 *a, Vec4 *b, Vec4 *c){
    a->x = fixmul(b->x, c->x);
    a->y = fixmul(b->y, c->y);
    a->z = fixmul(b->z, c->z);
    a->w = fixmul(b->w, c->w);
}

inline fixed vec4Dot(Vec4 *a, Vec4 *b){
    return fixmul(a->x, b->x) + fixmul(a->y, b->y) + fixmul(a->z, b->z) + fixmul(a->w, b->w);
}

