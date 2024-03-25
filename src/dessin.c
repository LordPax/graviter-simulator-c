#include "../include/dessin.h"
#include "../include/utils.h"

/**
 * @brief draw a disc
 *
 * @param p planet data structure
 * @param rende SDL render context
 */
void disque(Planete *p, SDL_Renderer *rende) {
    int d = 3 - (2 * p->r);
    int x = 0;
    int y = p->r;

    while (y >= x) {
        ligne_horizontale(p->x - x, p->y - y, 2 * x + 1, rende);
        ligne_horizontale(p->x - x, p->y + y, 2 * x + 1, rende);
        ligne_horizontale(p->x - y, p->y - x, 2 * y + 1, rende);
        ligne_horizontale(p->x - y, p->y + x, 2 * y + 1, rende);

        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void ligne_horizontale(int x, int y, int w, SDL_Renderer *rende) {
    SDL_Rect r;

    r.x = x;
    r.y = y;
    r.w = w;
    r.h = 1;

    SDL_RenderFillRect(rende, &r);
}

/**
 * @brief write text on screen
 *
 * @param x coordinate x
 * @param y coordinate y
 * @param text text to write
 * @param rende SDL render context
 */
void draw_text(int x, int y, char *text, SDL_Renderer *rende) {
    SDL_Color color = { 0, 0, 0, 255 };
    TTF_Font *font = TTF_OpenFont("ttf/Roboto-Regular.ttf", 25);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rende, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};

    SDL_RenderCopy(rende, texture, NULL, &rect);

    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * @brief show fps
 *
 * @param frameCount count of frame
 * @param lastFrameTime time of last frame
 * @param rende SDL render context
 */
void show_fps(int* frameCount, Uint32* lastFrameTime, SDL_Renderer* rende) {
    int fps = calculate_fps(frameCount, lastFrameTime);
    sdl_printf(rende, 10, 50, "Fps: %d", fps);
}

/**
 * @brief a printf for SDL
 *
 * @param rende SDL render context
 * @param x coordinate x
 * @param y coordinate y
 * @param fmt string format
 */
// TODO : refactor this function
void sdl_printf(SDL_Renderer* rende, int x, int y, const char *fmt, ...) {
    char fpsText[50];
    va_list args;
    va_start(args, fmt);

    vsprintf(fpsText, fmt, args);
    draw_text(x, y, fpsText, rende);

    va_end(args);
}
