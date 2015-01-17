#ifndef NUMBERS_H
#define NUMBERS_H

typedef int fixed;

#define FIXED_BITS  8
#define FIXED_ONE   (1<<FIXED_BITS)//0x100
#define FIXED_HALF  ((1<<FIXED_BITS)>>1)

#define f2i(A) ((A) >> FIXED_BITS)
#define i2f(A) ((A) << FIXED_BITS)

#define fixmul(A,B) f2i((A)*(B))
#define fixdiv(A,B) (i2f(A)/(B))

#define fixceil(A) f2i((A)+(FIXED_ONE-1))
#define fixinv(A) fixdiv(FIXED_ONE,(A))

short sqrt16(short x);
int isin(int x);
float mysinf(float a);

#endif //NUMBERS_H
