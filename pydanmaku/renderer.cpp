#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <stdbool.h>
#include "renderer.h"
#include "bullet.h"
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;
SDL_Texture *img = NULL;
int w=0, h=04;
bool render_inited = false;

void renderer_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
    win = SDL_CreateWindow(
            "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WIDTH, HEIGHT, SDL_WINDOW_SHOWN
    );

    ren = SDL_CreateRenderer(win, -1, 0);

    img = IMG_LoadTexture(ren, "./amulet.png");
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_RenderClear(ren);
    render_inited = true;

}

void render_bullet(Bullet bullet){
    SDL_Rect rect; rect.x=bullet.x-w/2; rect.y=bullet.y-h/2; rect.w=w; rect.h=h;
    SDL_RenderCopyEx(ren, img, NULL, &rect, 180*bullet.angle/M_PI, NULL, SDL_FLIP_NONE);
}

void render_bullets(std::list<Bullet> *bullets){
    if(!render_inited) return;
    SDL_RenderClear(ren);
    for (std::list<Bullet>::iterator b = bullets->begin(); b != bullets->end(); b++){
        render_bullet(*b);
    }
    SDL_RenderPresent(ren);
}

void renderer_close() {
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    render_inited = false;
}
