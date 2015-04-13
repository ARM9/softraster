#include "precompiled.h"
#include "globals.h"
#include "numbers.h"
#include "plot.h"
#include "sort.h"
#include "triangle.h"
#include "vectors.h"

unsigned g_EdgeBuffer[WIDTH * HEIGHT + 2];

void draw_horizontal_line(int x1, int y1, int x2, unsigned color)
{
    if(x2 < x1){
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    for(;x1 <= x2; x1++){
        plot(x1, y1, color);
    }
}

void sort_vertices_asc_y(Vec2 v[3])
{
    Vec2 vtmp;
    if(v[0].y > v[1].y){
        vtmp = v[0];
        v[0] = v[1];
        v[1] = vtmp;
    }
    if(v[0].y > v[2].y){
        vtmp = v[0];
        v[0] = v[2];
        v[2] = vtmp;
    }
    if(v[1].y > v[2].y){
        vtmp = v[1];
        v[1] = v[2];
        v[2] = vtmp;
    }
}


void draw_triangle(Vec2 v[3], unsigned color)
{
    //sort triangle Y coords
    sort_vertices_asc_y(v);
    if(v[0].y > HEIGHT || v[2].y < 0){
        return;
    }
    //clear edge buffer? just draw from min_y to max_y
    /*for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x+=2){
            g_EdgeBuffer[x + y * 2] = WIDTH;
            g_EdgeBuffer[x + 1 + y * 2] = 0;
        }
    }*/
    //draw lines to edge buffer
    //int y = min(HEIGHT, max(v[0].y, 0));
    if(v[0].y != v[1].y){
        for(int y = v[0].y; y < v[1].y; y++){
            draw_horizontal_line(v[0].x, y, v[1].x, color);
        }
    }else{
        // flat top
        for(int y = v[0].y; y < v[2].y; y++){
            draw_horizontal_line(v[0].x, y, v[1].x, color);
        }
    }
    // draw second triangle if not flat bottom
    if(v[1].y != v[2].y){
        for(int y = v[1].y; y < v[2].y; y++){
            draw_horizontal_line(v[1].x, y, v[2].x, color);
        }
    }
    //draw edge buffer
}

void fill_flat_bottom_triangle(Vec2 vt0, Vec2 vt1, Vec2 vt2, unsigned color)
{
    float slope1 = (float)(vt1.x - vt0.x) / (float)(vt1.y - vt0.y);
    float slope2 = (float)(vt2.x - vt0.x) / (float)(vt2.y - vt0.y);

    float x1 = vt0.x;
    float x2 = vt0.x + 0.5f;

    for (int scanlineY = vt0.y; scanlineY <= vt1.y; scanlineY++)
    {
        draw_horizontal_line((int)x1, scanlineY, (int)x2, color);
        x1 += slope1;
        x2 += slope2;
    }
}

void fill_flat_top_triangle(Vec2 vt0, Vec2 vt1, Vec2 vt2, unsigned color)
{
    float slope1 = (float)(vt2.x - vt0.x) / (float)(vt2.y - vt0.y);
    float slope2 = (float)(vt2.x - vt1.x) / (float)(vt2.y - vt1.y);

    float x1 = vt2.x;
    float x2 = vt2.x + 0.5f;

    for (int scanlineY = vt2.y; scanlineY > vt0.y; scanlineY--)
    {
        x1 -= slope1;
        x2 -= slope2;
        draw_horizontal_line((int)x1, scanlineY, (int)x2, color);
    }
}

void fill_triangle(Vec2 tri[3], unsigned color)
{
    Vec2 vt0, vt1, vt2, vt3;

    sort_vertices_asc_y(tri);
    vt0 = tri[0];
    vt1 = tri[1];
    vt2 = tri[2];

    if(vt1.y == vt2.y){
        fill_flat_bottom_triangle(vt0, vt1, vt2, color);
    }else if(vt0.y == vt1.y){
        fill_flat_top_triangle(vt0, vt1, vt2, color);
    }else{
    int t = (int)(vt0.x + ((float)(vt1.y - vt0.y) / (float)(vt2.y - vt0.y)) * (vt2.x - vt0.x));
    vt3.x = t;
    vt3.y = vt1.y;
    fill_flat_bottom_triangle(vt0, vt1, vt3, color);
    fill_flat_top_triangle(vt1, vt3, vt2, color);
    }
}

int crossProduct(Vec2 *a, Vec2 *b)
{
    return a->x * b->y - a->y * b->x;
}

// not very efficient
void barycentric_triangle(const Vec2 tri[3], unsigned color)
{

    int maxX = max(tri[0].x, max(tri[1].x, tri[2].x));
    int minX = min(tri[0].x, min(tri[1].x, tri[2].x));
    int maxY = max(tri[0].y, max(tri[1].y, tri[2].y));
    int minY = min(tri[0].y, min(tri[1].y, tri[2].y));

    Vec2 vs1 = {tri[1].x - tri[0].x, tri[1].y - tri[0].y};
    Vec2 vs2 = {tri[2].x - tri[0].x, tri[2].y - tri[0].y};

    for(int y = minY; y <= maxY; y++){
        for(int x = minX; x <= maxX; x++){
            Vec2 q = {x - tri[0].x, y - tri[0].y};

            float s = (float)crossProduct(&q, &vs2) / crossProduct(&vs1, &vs2);
            float t = (float)crossProduct(&vs1, &q) / crossProduct(&vs1, &vs2);

            if((s >= 0.f) && (t >= 0.f) && (s + t <= 1.f)){
                plot(x, y, color);
            }
        }
    }
}
