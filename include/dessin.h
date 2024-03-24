#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "graviter.h"

void disque(Planete *p, SDL_Renderer *rende);
void ligneHorizontale(int x, int y, int w, SDL_Renderer *rende);
void drawText(int x, int y, char *text, SDL_Renderer *rende);
void show_fps(int* frameCount, Uint32* lastFrameTime, SDL_Renderer* rende);

#endif
