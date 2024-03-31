#include "../include/graviter.h"
#include "../include/dessin.h"
#include "../include/planete.h"
#include "../include/utils.h"

/**
 * @brief initialize data for every planet
 *
 * @param nb number of planet
 * @param masse maximum mass of every planet
 */
Planete *init_planete(int nb, int masse) {
    Planete *planete = malloc(sizeof(Planete) * nb);
    if (planete == NULL) return NULL;

    srand(time(NULL));

    for (int i = 0; i < nb; ++i){
        planete[i].x = rand() % W;
        planete[i].y = rand() % H;
        planete[i].vx = 0;
        planete[i].vy = 0;
        planete[i].dirx = 0;
        planete[i].diry = 0;
        planete[i].masse = rand() % masse;
        planete[i].r = sqrt(planete[i].masse);
        planete[i].distCrit = planete[i].r * sqrt(2);
        planete[i].exist = true;
    }

    return planete;
}

/**
 * @brief reinitialize data for every planet
 *
 * @param p array of planet
 * @param nb max number of planet
 * @param masse maximum mass of every planet
 * @return new array of planet
 */
Planete *reinit_planete(Planete *p, int nb, int masse) {
    free(p);
    p = init_planete(nb, masse);
    return p;
}

/**
 * @brief make graphical render of every planet
 *
 * @param p planet data structure
 * @param nb number of every planet
 * @param rende render context
 */
void spawn_planete(Planete *p, int nb, SDL_Renderer *rende, Camera *cam, bool *show_info) {
    SDL_SetRenderDrawColor(rende, 0, 0, 0, SDL_ALPHA_OPAQUE);
    int x, y;
    for (int i = 0; i < nb; ++i) {
        if(!p[i].exist) continue;

        x = p[i].x + cam->x;
        y = p[i].y + cam->y;
        disque(rende, x, y, p[i].r);

        if (*show_info)
            show_planete_info(&p[i], cam, rende);
    }
}

/**
 * @brief update data for every planet
 *
 * @param p all planete
 * @param nb number of planet
 */
void update_planete(Planete *p, int nb) {
    for (int i = 0; i < nb; ++i) {
        if (!p[i].exist) continue;

        for (int j = 0; j < nb; ++j) {
            if(!p[j].exist) continue;
            graviter_planete(&p[i], &p[j]);
        }

        p[i].x += p[i].vx;
        p[i].y += p[i].vy;
    }
}

/**
 * @brief make gravity beetwin 2 planet
 *
 * @param pThis actual planet
 * @param p other planet
 */
void graviter_planete(Planete *pThis, Planete *p) {
    int dx = p->x - pThis->x;
    int dy = p->y - pThis->y;
    int dist = dx * dx + dy * dy;

    if (dist == 0) return;

    int dist2 = sqrt(dist);

    if (dist2 < (pThis->r + p->r)) {
        if (p->masse <= pThis->masse) {
            pThis->masse += p->masse;
            pThis->x = (pThis->x * pThis->masse + p->x * p->masse) / (pThis->masse + p->masse);
            pThis->y = (pThis->y * pThis->masse + p->y * p->masse) / (pThis->masse + p->masse);
            pThis->vx = (pThis->masse * pThis->vx + p->masse + p->vx) / (pThis->masse + p->masse);
            pThis->vy = (pThis->masse * pThis->vy + p->masse + p->vy) / (pThis->masse + p->masse);

            p->exist = false;
            pThis->r = sqrt(pThis->masse);
        }
        return;
    }

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

/**
 * @brief count number of planet
 *
 * @param p array of planet
 * @return number of planet
 */
int nb_planete(Planete *p, int total) {
    int nb = 0;

    for (int i = 0; i < total; ++i)
        if (p[i].exist) nb++;

    return nb;
}

/**
 * @brief show number of planet
 *
 * @param rende context of sdl
 * @param p array of planet
 */
void show_nb_planete(Planete *p, int total, SDL_Renderer *rende) {
    int nb = nb_planete(p, total);
    TextConf conf = {0, 0, 0, 255, 100, 25};
    sdl_printf(rende, conf, 10, 100, "Nombre de planete : %d/%d", nb, total);
}

/**
 * @brief show information of a planet
 *
 * @param p planet to show
 * @param cam camera position
 * @param rende sdl render context
 */
void show_planete_info(Planete *p, Camera *cam, SDL_Renderer *rende) {
    TextConf conf = {0, 0, 0, 255, 100, 10};
    int x = p->x + p->r + cam->x + 10;
    int y = p->y + cam->y;

    sdl_printf(rende, conf, x, y, "masse : %.2f", p->masse);
    sdl_printf(rende, conf, x, y + 10, "x : %.2f", p->x);
    sdl_printf(rende, conf, x, y + 20, "y : %.2f", p->y);
}
