#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

int calculate_fps(int* frameCount, Uint32* lastFrameTime);
void limitFps(unsigned int limit);
void SDL_Exit(const char *msg);

#endif
