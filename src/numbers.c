#include "precompiled.h"
#include "numbers.h"

short sqrt16(short x)
{
  short res = 0;
  short bit = 1 << 14;

  while(bit > x)
    bit >>= 2;

  while(bit != 0){
    if(x >= res + bit){
      x -= res + bit;
      res = (res >> 1) + bit;
    }else{
      res >>= 1;
    }
    bit >>= 2;
  }
  return res;
}

/*
 * isin algorithm by the amazing cearn http://www.coranac.com/
 */
/* 0x2000=q1
 * 0x4000=q2
 * 0x6000=q3
 * 0x8000=q4
 */
int isin(int x)
{
  const int qN = 13, qA = 12, qP = 15, qR = 2*qN-qP, qS = qN+qP+1-qA;
  x = x << (30 - qN);
  if ((x^(x<<1)) < 0)
    x = (1 << 31) - x;
  x = x >> (30 - qN);
  return x * ((3 << qP) - (x * x >> qR)) >> qS;
}

float mysinf(float a)
{
  float t = a, y = 0.f;
  float d = 1.f;
  while((y = 0.f) || (fabsf(t/y) > 1e-2)) {
    y = y + t;
    t = - (t * a * a) / ((d + 1) * (d + 2));
    d = d + 2;
  }
  return t;
}
// vim:sts=2 sw=2
