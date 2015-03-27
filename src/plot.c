#include "precompiled.h"
#include "numbers.h"
#include "plot.h"

inline void set_screen(Screen_t * const p_screen){
  g_Screen = p_screen;
}

inline void plot(int x, int y, int color) {
  g_Screen->pixels[y * g_Screen->pitch + x] = color;
  /*g_Screen->pixels[y * 320 + x] = color;*/
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
  int dx, dy, e;
  int incx, incy, inc1, inc2;
  int x,y;

  dx = abs(x2 - x1);
  dy = abs(y2 - y1);

  incx = 1;
  if(x2 < x1) incx = -1;
  incy = 1;
  if(y2 < y1) incy = -1;
  x=x1;
  y=y1;

  plot(x, y, color);
  if(dx > dy){
    e = 2*dy - dx;
    inc1 = 2*( dy -dx);
    inc2 = 2*dy;
    for(int i = 0; i < dx; i++){
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
    e = 2*dx - dy;
    inc1 = 2*( dx - dy);
    inc2 = 2*dx;
    for(int i = 0; i < dy; i++){
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

void draw_rotated_image_i(int *img, int width, int height, int angle)
{
  int hwidth = width / 2;
  int hheight = height / 2;

  int sinma = isin(angle);
  int cosma = icos(angle);

  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      int xt = x - hwidth;
      int yt = y - hheight;

      /*int xs = (int)round((cosma * xt - sinma * yt) + hwidth);*/
      /*int ys = (int)round((sinma * xt + cosma * yt) + hheight);*/

#define fixmul32(a, b) (((a)*(b))>>12)
      /*int xs = fixmul32(xt, cosma) - fixmul32(yt, sinma) + hwidth;*/
      /*int ys = fixmul32(xt, sinma) + fixmul32(yt, cosma) + hheight;*/
      int xs = fixmul32(yt, sinma) + fixmul32(xt, cosma) + hwidth;
      int ys = fixmul32(yt, cosma) - fixmul32(xt, sinma) + hheight;

      if(xs >= 0 && xs < width && ys >= 0 && ys < height) {
        /* set target pixel (x,y) to color at (xs,ys) */
        plot(x, y, img[ys * height + xs]&0xFFFF);
      } else {
        plot(x, y, 0);
      }
    }
  }
}

void draw_rotated_image(int *img, int width, int height, double angle)
{
  int hwidth = width / 2;
  int hheight = height / 2;

  double sinma = sin(-angle);
  double cosma = cos(-angle);

  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      int xt = x - hwidth;
      int yt = y - hheight;

      int xs = (int)round((cosma * xt - sinma * yt) + hwidth);
      int ys = (int)round((sinma * xt + cosma * yt) + hheight);

      if(xs >= 0 && xs < width && ys >= 0 && ys < height) {
        /* set target pixel (x,y) to color at (xs,ys) */
        plot(x, y, img[ys * height + xs]);
      } else {
        plot(x, y, 0);
      }
    }
  }
}
// vim:sts=2 sw=2
