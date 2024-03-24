#include "../include/graviter.h"
#include "../include/dessin.h"
#include "../include/utils.h"

/**
 * @brief draw a disc
 *
 * @param p planet data structure
 * @param rende SDL render context
 */
void disque(Planete *p, SDL_Renderer *rende) {
    int d, y, x;

    d = 3 - (2 * p->r);
    x = 0;
    y = p->r;

    while (y >= x) {
        ligneHorizontale(p->x - x, p->y - y, 2 * x + 1, rende);
        ligneHorizontale(p->x - x, p->y + y, 2 * x + 1, rende);
        ligneHorizontale(p->x - y, p->y - x, 2 * y + 1, rende);
        ligneHorizontale(p->x - y, p->y + x, 2 * y + 1, rende);

        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void ligneHorizontale(int x, int y, int w, SDL_Renderer *rende) {
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
void drawText(int x, int y, char *text, SDL_Renderer *rende) {
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
    char fpsText[10];
    int fps = calculate_fps(frameCount, lastFrameTime);

    sprintf(fpsText, "Fps: %d", fps);
    drawText(10, 50, fpsText, rende);
}
