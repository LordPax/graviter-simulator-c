#ifndef PLANETE_H
#define PLANETE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "graviter.h"

typedef struct {
    float x, y; // coordonnée x, y
    float vx, vy; // vitesse vx, vy
    float r; // rayon de la planete
    float masse; // masse de la planete
    float distCrit; // distance critique de collision
    float dirx, diry; // direction en x, y
    float angle;
    bool exist;
} Planete;

Planete *init_planete(int nb, int masse);
Planete *reinit_planete(Planete *p, int nb, int masse);
void spawn_planete(Planete *p, int nb, SDL_Renderer *rende, Camera *cam, bool *show_info);
void update_planete(Planete *p, int nb);
void graviter_planete(Planete *pThis, Planete *p);
int nb_planete(Planete *p, int total);
void show_nb_planete(Planete *p, int x, int y, int total, SDL_Renderer *rende);
void show_planete_info(Planete *p, Camera *cam, SDL_Renderer *rende);

#endif
