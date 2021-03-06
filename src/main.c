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

/****************************************************/

Vec3 tri3[3] =
    {{150, 40, 1}
    ,{200, 55, 1}
    ,{130, 70, 1}};

Vec2 tri[3] =
    {{150, 40 }
    ,{200, 55}
    ,{130, 70 }};

int main(int argc, char *argv[]) {
    /* init SDL */

    SDL_Window *mainWindow;
    SDL_Renderer *mainRenderer;
    SDL_Texture *framebuffer;

    Screen_t screen = {WIDTH, HEIGHT, NULL, 0};//WIDTH};
    set_screen(&screen); // it's on the stack I guess but fuck it

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

    //int *buffer = malloc(ballBitmapLen);
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


        tri[0].x = tri3[0].x + (isin((frame<<7)+0x4000)>>7);
        tri[1].x = tri3[1].x + (isin((frame<<7)+0x2000)>>7);
        tri[2].x = tri3[2].x + (isin((frame<<7)+0x6000)>>7);
        tri[0].y = tri3[0].y + (isin((frame<<7)+0x4000)>>7);
        tri[1].y = tri3[1].y + (isin((frame<<7)+0x8000)>>7);
        tri[2].y = tri3[2].y + (isin((frame<<7)+0x6000)>>7);

        draw_triangle(tri, 0x0000ff);
        tri[0].y += 50;
        tri[1].y += 50;
        tri[2].y += 50;
        barycentric_triangle(tri, 0x00ff00);
        tri[0].y -= 50;
        tri[1].y -= 50;
        tri[2].y -= 50;

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

