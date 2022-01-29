#ifndef GRAVITER_H
#define GRAVITER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <time.h>

#define W 900
#define H 650
#define LIMIT 16

typedef enum exist {
    false,
    true
} Exist;

typedef struct Planete {
    float x, y; // coordonnée x, y
    float vx, vy; // vitesse vx, vy
    float r; // rayon de la planete
    float masse; // masse de la planete
    float distCrit; // distance critique de collision
    float dirx, diry; // direction en x, y
    float angle;
    Exist exist;
} Planete;

void SDL_Exit(const char *msg);
void Init_Planete(Planete *p, int nb, int masse);
void disque(Planete *p, SDL_Renderer *rende);
void ligneHorizontale(int x, int y, int w, SDL_Renderer *rende);
void Spawn_Planete(Planete *p, int nb, SDL_Renderer *rende);
void Update_Planete(Planete *pThis, Planete *p, int nb);
void limitFps(unsigned int limit);
void Graviter_Planete(Planete *pThis, Planete *p);
//void cercle(Planete *p, int coul);

#endif
