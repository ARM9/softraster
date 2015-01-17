#include "precompiled.h"
#include "numbers.h"
#include "vectors.h"

/* 2D Vectors ************************/
inline void vec2Set(vec2 *v, fixed x, fixed y){
    v->x = x;
    v->y = y;
}

inline void vec2Add(vec2 *a, vec2 *b, vec2 *c){
    a->x = b->x + c->x;
    a->y = b->y + c->y;
}

inline void vec2Sub(vec2 *a, vec2 *b, vec2 *c){
    a->x = b->x - c->x;
    a->y = b->y - c->y;
}

inline void vec2Mul(vec2 *a, vec2 *b, vec2 *c){
    a->x = fixmul(b->x, c->x);
    a->y = fixmul(b->y, c->y);
}

inline fixed vec2Dot(vec2 *a, vec2 *b){
    return fixmul(a->x, b->x) + fixmul(a->y, b->y);
}

/* 3D Vectors ************************/
inline void vec3Set(vec3 *v, fixed x, fixed y, fixed z){
    v->x = x;
    v->y = y;
    v->z = z;
}

inline void vec3Add(vec3 *a, vec3 *b, vec3 *c){
    a->x = b->x + c->x;
    a->y = b->y + c->y;
    a->z = b->z + c->z;
}

inline void vec3Sub(vec3 *a, vec3 *b, vec3 *c){
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;
}

inline void vec3Mul(vec3 *a, vec3 *b, vec3 *c){
    a->x = fixmul(b->x, c->x);
    a->y = fixmul(b->y, c->y);
    a->z = fixmul(b->z, c->z);
}

inline fixed vec3Dot(vec3 *a, vec3 *b){
    return fixmul(a->x, b->x) + fixmul(a->y, b->y) + fixmul(a->z, b->z);
}

inline void vec3Cross(vec3 *a, vec3 *b, vec3 *c){
    vec3 t;
    t.x = fixmul(b->y, c->z) - fixmul(b->z, c->y);
    t.y = fixmul(b->z, c->x) - fixmul(b->x, c->z);
    t.z = fixmul(b->x, c->y) - fixmul(b->y, c->x);
    vec3Set(a, t.x, t.y, t.z);
}

/* 4D Vectors ************************/
inline void vec4Set(vec4 *v, fixed x, fixed y, fixed z, fixed w){
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

inline void vec4Add(vec4 *a, vec4 *b, vec4 *c){
    a->x = b->x + c->x;
    a->y = b->y + c->y;
    a->z = b->z + c->z;
    a->w = b->w + c->w;
}

inline void vec4Sub(vec4 *a, vec4 *b, vec4 *c){
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;
    a->w = b->w - c->w;
}

inline void vec4Mul(vec4 *a, vec4 *b, vec4 *c){
    a->x = fixmul(b->x, c->x);
    a->y = fixmul(b->y, c->y);
    a->z = fixmul(b->z, c->z);
    a->w = fixmul(b->w, c->w);
}

inline fixed vec4Dot(vec4 *a, vec4 *b){
    return fixmul(a->x, b->x) + fixmul(a->y, b->y) + fixmul(a->z, b->z) + fixmul(a->w, b->w);
}

