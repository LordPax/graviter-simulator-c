#include "../include/graviter.h"

void SDL_Exit(const char *msg){
	SDL_Log("Erreur : %s > %s\n", msg, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void disque(Planete *p, SDL_Renderer *rende){
	int d, y, x;

	d = 3 - (2 * p->r);
	x = 0;
	y = p->r;

	while (y >= x){
		ligneHorizontale(p->x - x, p->y - y, 2 * x + 1, rende);
		ligneHorizontale(p->x - x, p->y + y, 2 * x + 1, rende);
		ligneHorizontale(p->x - y, p->y - x, 2 * y + 1, rende);
		ligneHorizontale(p->x - y, p->y + x, 2 * y + 1, rende);

		if (d < 0)
			d = d + (4 * x) + 6;
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}

		x++;
	}
}

void ligneHorizontale(int x, int y, int w, SDL_Renderer *rende){
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;
 
  SDL_RenderFillRect(rende, &r);
}

void limitFps(unsigned int limit){
	unsigned int ticks = SDL_GetTicks();

	if(limit < ticks)
		return;
	else if(limit > ticks + LIMIT)
		SDL_Delay(LIMIT);
	else
		SDL_Delay(limit - ticks);
}
