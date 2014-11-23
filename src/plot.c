#include "precompiled.h"
#include "plot.h"

inline void set_screen(screen_t *p_screen){
  g_Screen = p_screen;
}

inline void plot(int x, int y, int color) {
  g_Screen->pixels[y * g_Screen->pitch + x] = color;
}

inline void framebuffer_clear(int color)
{
  for(int y = 0; y < g_Screen->height; y++){
    for(int x = 0; x < g_Screen->width; x++){
      plot(x, y, color);
    }
  }
}

void draw_circle(int u, int v, int r, int color)
{
    int sqrr, rsqrt2, x, y;
    sqrr = r * r;
    rsqrt2 = r / sqrt(2);
    for(y = 0; y <= rsqrt2; y++){
        x = sqrt(sqrr - y * y);
        plot( x+u, y+v, color);
        plot( y+u, x+v, color);
        plot(-x+u, y+v, color);
        plot(-y+u, x+v, color);
        plot( x+u,-y+v, color);
        plot( y+u,-x+v, color);
        plot(-y+u,-x+v, color);
        plot(-x+u,-y+v, color);
    }
}

void draw_circle_fast(int x1, int y1, int r, int color)
{
  int x2 = r;
  int y2 = 0;
  int err = 1-x2;
  while(x2 >= y2){
    plot(x2 + x1, y2 + y1, color);
    plot(y2 + x1, x2 + y1, color);
    plot(-x2 + x1, y2 + y1, color);
    plot(-y2 + x1, x2 + y1, color);
    plot(-x2 + x1, -y2 + y1, color);
    plot(-y2 + x1, -x2 + y1, color);
    plot(x2 + x1, -y2 + y1, color);
    plot(y2 + x1, -x2 + y1, color);
    y2++;
    if(err < 0){
      err += 2 * y2 + 1;
    }else{
      x2--;
      err += 2 * (y2 - x2 + 1);
    }
  }
}

void draw_line(int x1,int y1,int x2,int y2, int color)
{
  int dx, dy, i, e;
  int incx, incy, inc1, inc2;
  int x,y;

  dx = x2 - x1;
  dy = y2 - y1;

  if(dx < 0) dx = -dx;
  if(dy < 0) dy = -dy;
  incx = 1;
  if(x2 < x1) incx = -1;
  incy = 1;
  if(y2 < y1) incy = -1;
  x=x1;
  y=y1;

  if(dx > dy){
    plot(x, y, color);
    e = 2*dy - dx;
    inc1 = 2*( dy -dx);
    inc2 = 2*dy;
    for(i = 0; i < dx; i++){
      if(e >= 0){
        y += incy;
        e += inc1;
      }else{
        e += inc2;
      }
      x += incx;
      plot(x, y, color);
    }
  }else{
    plot(x, y, color);
    e = 2*dx - dy;
    inc1 = 2*( dx - dy);
    inc2 = 2*dx;
    for(i = 0; i < dy; i++){
      if(e >= 0){
        x += incx;
        e += inc1;
      }else{
        e += inc2;
      }
      y += incy;
      plot(x, y, color);
    }
  }
}

void draw_line2(int x1, int y1, int x2, int y2, int color)
{
  int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
  int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    plot(x1, y1, color);
    if (x1==x2 && y1==y2) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x1 += sx; }
    if (e2 < dy) { err += dx; y1 += sy; }
  }
}
// vim:sts=2 sw=2
