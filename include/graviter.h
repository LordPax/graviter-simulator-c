#ifndef GRAVITER_H
#define GRAVITER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

/* #define W 900 */
/* #define H 650 */
#define W 1920
#define H 1080
#define LIMIT 16

void event_func(SDL_bool *cont, SDL_Event *event, bool *pause);

#endif
