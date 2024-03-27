#include "../include/dessin.h"
#include "../include/utils.h"

/**
 * @brief draw a disc
 *
 * @param p planet data structure
 * @param rende SDL render context
 */
void disque(int px, int py, int pr, SDL_Renderer *rende) {
    int d = 3 - (2 * pr);
    int x = 0;
    int y = pr;

    while (y >= x) {
        ligne_horizontale(rende, px - x, py - y, 2 * x + 1);
        ligne_horizontale(rende, px - x, py + y, 2 * x + 1);
        ligne_horizontale(rende, px - y, py - x, 2 * y + 1);
        ligne_horizontale(rende, px - y, py + x, 2 * y + 1);

        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void ligne_horizontale(SDL_Renderer *rende, int x, int y, int w) {
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
 * @param rende SDL render context
 * @param x coordinate x
 * @param y coordinate y
 * @param text text to write
 * @param conf text configuration (r, g, b, a, len, fontSize)
 */
void draw_text(SDL_Renderer *rende, TextConf conf, int x, int y, char *text) {
    SDL_Color color = { conf.r, conf.g, conf.b, conf.a };
    TTF_Font *font = TTF_OpenFont("ttf/Roboto-Regular.ttf", conf.fontSize);
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
 * @param rende SDL render context
 * @param frameCount count of frame
 * @param lastFrameTime time of last frame
 */
void show_fps(SDL_Renderer* rende, int* frameCount, Uint32* lastFrameTime) {
    int fps = calculate_fps(frameCount, lastFrameTime);
    TextConf conf = {0, 0, 0, 255, 100, 25};
    sdl_printf(rende, conf, 10, 50, "Fps: %d", fps);
}
