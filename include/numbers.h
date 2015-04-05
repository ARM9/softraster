#ifndef NUMBERS_H
#define NUMBERS_H
#include <stdint.h>

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;

typedef s32 fixed;

#define FIXED_BITS  8
#define FIXED_ONE   (1<<FIXED_BITS)//0x100
#define FIXED_HALF  ((1<<FIXED_BITS)>>1)

#define f2i(A) ((A) >> FIXED_BITS)
#define i2f(A) ((A) << FIXED_BITS)

#define fixmul(A,B) f2i((A)*(B))
#define fixdiv(A,B) (i2f(A)/(B))

#define fixceil(A) f2i((A)+(FIXED_ONE-1))
#define fixinv(A) fixdiv(FIXED_ONE,(A))

s16 sqrt16(s16 x);
s32 isin(s32 x);
#define icos(x) isin(x+0x2000)
float mysinf(float a);

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

#endif //NUMBERS_H
