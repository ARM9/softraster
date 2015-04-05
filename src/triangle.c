#include "precompiled.h"
#include "globals.h"
#include "numbers.h"
#include "plot.h"
#include "sort.h"
#include "triangle.h"
#include "vectors.h"

u16 g_EdgeBuffer[WIDTH * HEIGHT + 2];

/*void fill_triangle(Tri_t *tri)
{
    //sort triangle Y coords
    //bucket_sort(tri);
    //clear edge buffer
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x+=2){
            g_EdgeBuffer[x + y * 2] = WIDTH;
            g_EdgeBuffer[x + 1 + y * 2] = 0;
        }
    }
    //draw lines to edge buffer
    
    //draw edge buffer
    
}
*/

int crossProduct(Vec2 *a, Vec2 *b)
{
    return a->x * b->y - a->y * b->x;
}

// not very efficient
void barycentric_triangle(const Vec2 *tri, int color)
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
