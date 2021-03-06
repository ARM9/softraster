#ifndef PLOT_H
#define PLOT_H value

#include "triangle.h"

typedef struct Screen_t {
  int width, height;
  uint32_t *pixels;
  int pitch;
} Screen_t;

Screen_t *g_Screen;

void set_screen(Screen_t * const p_screen);

void plot(int x, int y, int color);
void framebuffer_clear(int color);

void draw_circle_loop(int u, int v, int r, int color);
void draw_circle_branch(int u, int v, int r, int color);

void draw_line(int x1, int y1, int x2, int y2, int color);
void draw_line2(int x1, int y1, int x2, int y2, int color);

#endif //PLOT_H
// vim:sts=2
