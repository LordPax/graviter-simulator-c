#ifndef GRAVITER_H
#define GRAVITER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define W 900
#define H 650
#define LIMIT 16

typedef struct Planete {
    float x, y; // coordonnée x, y
    float vx, vy; // vitesse vx, vy
    float r; // rayon de la planete
    float masse; // masse de la planete
    float distCrit; // distance critique de collision
    float dirx, diry; // direction en x, y
    float angle;
    bool exist;
} Planete;

Planete* Init_Planete(int nb, int masse);
void Spawn_Planete(Planete *p, int nb, SDL_Renderer *rende);
void Update_Planete(Planete *pThis, Planete *p, int nb);
void Graviter_Planete(Planete *pThis, Planete *p);
void eventFunc(SDL_bool *cont, SDL_Event *event, bool *pause);

#endif
