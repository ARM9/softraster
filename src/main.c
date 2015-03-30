#include "precompiled.h"

#include "assembly.h"

#include "assets.h"

#include "globals.h"
#include "list.h"
#include "lzss.h"
#include "numbers.h"
#include "plot.h"
#include "profile.h"
#include "triangle.h"
#include "matrix2.h"
#include "vectors.h"

typedef struct Poly_t {
    Tri_t *triangles;
    int size;
} Poly_t;

typedef struct Entity3d_t {
    Vec3 position;
    Poly_t *polygon;
} Entity3d_t;

Entity3d_t *object3d_new(Vec3 p_position, Poly_t *p_polygon)
{
    Entity3d_t *t_obj = malloc(sizeof(Entity3d_t));
    t_obj->position.x = p_position.x;
    t_obj->position.y = p_position.y;
    t_obj->position.z = p_position.z;
    t_obj->polygon = p_polygon;
    return t_obj;
}

/****************************************************/
const Tri_t tri[] =
    {{{{ 20, 10, 10, 0xff0000 }}}
    ,{{{ 30, 30, 10, 0xff0000 }}}
    ,{{{ 10, 30, 10, 0xff0000 }}}};

Poly_t cube = {tri, sizeof(tri)};

int main(int argc, char *argv[]) {
    /* init SDL */

    argc = argv[0];
    SDL_Window *mainWindow;
    SDL_Renderer *mainRenderer;
    SDL_Texture *framebuffer;

    Screen_t screen = {WIDTH, HEIGHT, NULL, 0};//WIDTH};
    set_screen(&screen); // it's on the stack I guess but fuck it

    Entity3d_t *player = object3d_new((Vec3){10, 10, 10}, &cube);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "failed to init SDL\n");
        return 1;
    }
    if(!(mainWindow = SDL_CreateWindow("softraster", 450, 250, screen.width, screen.height, 0))) {
        fprintf(stderr, "failed to create window\n");
        SDL_Quit();
        return 0;
    }
    if(!(mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC))) {
        fprintf(stderr, "failed to create renderer\n");
        SDL_Quit();
        return 0;
    }

    framebuffer = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen.width, screen.height);

    /* main loop*/
    int frame = 0;

    int bg_color = 0x4092c4;

    int running = 1;

    int *buffer = malloc(ballBitmapLen);
    //lzssDecompress(buffer, (char*)ball_lz77Bitmap);

    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                    }
                    break;
            }
        }
        
        SDL_LockTexture(framebuffer, NULL, (void*)&screen.pixels, &screen.pitch);
        screen.pitch >>= 2;

        framebuffer_clear(bg_color);

        draw_line(50, 50, 50+(int)(sinf(frame/180.f)*20.f), 50+(int)(cosf(frame/180.f)*20.f), 0xfeedba);
        draw_line(50+(int)(sinf(frame/180.f)*20.f), 100+(int)(cosf(frame/180.f)*20.f), 50, 100, 0xfeedba);

        draw_line2(80, 50, 80+(int)(sinf(frame/180.f)*20.f), 50+(int)(cosf(frame/180.f)*20.f), 0xbada55);
        draw_line2(80+(int)(sinf(frame/180.f)*20.f), 100+(int)(cosf(frame/180.f)*20.f), 80, 100, 0xbada55);
        draw_line2(1, 1, 1, 1, 0xbada55);

        draw_line2(20, 20, 20-2, 20-14, 0xff0000);

        draw_circle_loop(100, 100, 100, 0x123456);
        draw_circle_branch(150, 50, 50, 0xabcdef);

        plot(frame % screen.width, (100+(isin(frame<<8)>>8)) % screen.height, 0xffffff);

        static double angle = 0.0;
        angle += 0.01;
        /*draw_rotated_image(ballBitmap, 64, 64, angle);*/
        static int iangle = 0;
        iangle+=32;
        //draw_rotated_image_i(ballBitmap, 64, 64, iangle);

        SDL_UnlockTexture(framebuffer);

        SDL_RenderCopy(mainRenderer, framebuffer, NULL, NULL);
        SDL_RenderPresent(mainRenderer);
        frame++;
    }

    SDL_DestroyTexture(framebuffer);

    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}

