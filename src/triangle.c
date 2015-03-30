#include "precompiled.h"
#include "globals.h"
#include "triangle.h"
//#include "types.h"
#include "vectors.h"

int g_EdgeBuffer[WIDTH * HEIGHT + 2];

void fill_triangle(Tri_t *tri)
{
    //sort triangle Y coords
    bucket_sort(tri);
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

