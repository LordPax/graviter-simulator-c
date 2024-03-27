#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "planete.h"

typedef struct {
    int r;
    int g;
    int b;
    int a;
    int len;
    int fontSize;
} TextConf;

/* void disque(Planete *p, SDL_Renderer *rende); */
void disque(int px, int py, int pr, SDL_Renderer *rende);
void ligne_horizontale(SDL_Renderer *rende, int x, int y, int w);
void draw_text(SDL_Renderer *rende, TextConf conf, int x, int y, char *text);
void show_fps(SDL_Renderer* rende, int* frameCount, Uint32* lastFrameTime);

#endif
