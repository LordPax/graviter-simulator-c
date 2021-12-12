#include "../include/graviter.h"

void Init_Planete(Planete *p, int nb, int masse){
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

void Spawn_Planete(Planete *p, int nb, SDL_Renderer *rende){
	SDL_SetRenderDrawColor(rende, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < nb; ++i)
		if(p[i].exist)
			disque(&p[i], rende);
}

void Update_Planete(Planete *pThis, Planete *p, int nb){
	for (int i = 0; i < nb; ++i)
		if(p[i].exist)
			Graviter_Planete(pThis, &p[i]);

	pThis->x += pThis->vx;
	pThis->y += pThis->vy;
}

void Graviter_Planete(Planete *pThis, Planete *p){
	int dx = p->x - pThis->x;
	int dy = p->y - pThis->y;
	int dist = dx * dx + dy * dy;

	if(dist != 0){
		int dist2 = sqrt(dist);
		if(dist2 < (pThis->r + p->r)){
			if(p->masse < pThis->masse){
				pThis->masse += p->masse;
				pThis->x = (pThis->x * pThis->masse + p->x * p->masse) / (pThis->masse + p->masse);
				pThis->y = (pThis->y * pThis->masse + p->y * p->masse) / (pThis->masse + p->masse);
				pThis->vx = (pThis->masse * pThis->vx + p->masse + p->vx) / (pThis->masse + p->masse);
				pThis->vy = (pThis->masse * pThis->vy + p->masse + p->vy) / (pThis->masse + p->masse);

				p->exist = false;
				pThis->r = sqrt(pThis->masse);
			}
		}
		else{
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
