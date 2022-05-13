#include "../include/graviter.h"

/**
 * @brief initialize data for every planet
 *
 * @param p planet data structure
 * @param nb number of planet
 * @param masse maximum mass of every planet
 */
void Init_Planete(Planete *p, int nb, int masse) {
    srand(time(NULL));
    for (int i = 0; i < nb; ++i){
        p[i].x = rand() % W;
        p[i].y = rand() % H;
        p[i].vx = 0;
        p[i].vy = 0;
        p[i].dirx = 0;
        p[i].diry = 0;
        p[i].masse = rand() % masse;
        p[i].r = sqrt(p[i].masse);
        p[i].distCrit = p[i].r * sqrt(2);
        p[i].exist = true;
    }
}

/**
 * @brief make graphical render of every planet
 *
 * @param p planet data structure
 * @param nb number of every planet
 * @param rende render context
 */
void Spawn_Planete(Planete *p, int nb, SDL_Renderer *rende) {
    SDL_SetRenderDrawColor(rende, 0, 0, 0, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < nb; ++i)
        if(p[i].exist)
            disque(&p[i], rende);
}

/**
 * @brief update data for every planet
 *
 * @param pThis actual planet
 * @param p other planet
 * @param nb number of planet
 */
void Update_Planete(Planete *pThis, Planete *p, int nb) {
    for (int i = 0; i < nb; ++i)
        if(p[i].exist)
            Graviter_Planete(pThis, &p[i]);

    pThis->x += pThis->vx;
    pThis->y += pThis->vy;
}

/**
 * @brief make gravity beetwin 2 planet
 *
 * @param pThis actual planet
 * @param p other planet
 */
void Graviter_Planete(Planete *pThis, Planete *p) {
    int dx = p->x - pThis->x;
    int dy = p->y - pThis->y;
    int dist = dx * dx + dy * dy;

    if(dist != 0) {
        int dist2 = sqrt(dist);
        if(dist2 < (pThis->r + p->r)) {
            if(p->masse < pThis->masse) {
                pThis->masse += p->masse;
                pThis->x = (pThis->x * pThis->masse + p->x * p->masse) / (pThis->masse + p->masse);
                pThis->y = (pThis->y * pThis->masse + p->y * p->masse) / (pThis->masse + p->masse);
                pThis->vx = (pThis->masse * pThis->vx + p->masse + p->vx) / (pThis->masse + p->masse);
                pThis->vy = (pThis->masse * pThis->vy + p->masse + p->vy) / (pThis->masse + p->masse);

                p->exist = false;
                pThis->r = sqrt(pThis->masse);
            }
        }
        else {
            float force = p->masse / dist;
            float angle = atan2(p->y - pThis->y, p->x - pThis->x);
            float dirx = force * cos(angle);
            float diry = force * sin(angle);

            pThis->dirx = dirx;
            pThis->diry = diry;
            pThis->angle = angle;

            pThis->vx += dirx;
            pThis->vy += diry;
        }
    }
}

/**
 * @brief manage event
 *
 * @param cont determine if script continue or not
 * @param event sdl event to manage event
 * @param pause pause the "simulation"
 */
void eventFunc(SDL_bool *cont, SDL_Event *event, _Bool *pause) {
    switch(event->type) {
        case SDL_QUIT :
            *cont = SDL_FALSE;
            printf("Graviter : Programme quiter\n");
            break;
        case SDL_KEYDOWN :
            switch(event->key.keysym.sym) {
                case SDLK_ESCAPE :
                    *cont = SDL_FALSE;
                    printf("Graviter : Programme quiter\n");
                    break;

                case SDLK_a :
                    *pause = !(*pause);
                    if (*pause == false)
                        printf("Graviter : Programme en pause\n");
                    else
                        printf("Graviter : Programme en route\n");
                    break;
            }
            break;
    }
}
