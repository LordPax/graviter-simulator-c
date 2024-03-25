#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "planete.h"

void disque(Planete *p, SDL_Renderer *rende);
void ligne_horizontale(int x, int y, int w, SDL_Renderer *rende);
void draw_text(int x, int y, char *text, SDL_Renderer *rende);
void show_fps(int* frameCount, Uint32* lastFrameTime, SDL_Renderer* rende);
void sdl_printf(SDL_Renderer* rende, int x, int y, const char *fmt, ...);

#endif
