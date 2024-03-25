#include "../include/graviter.h"
#include "../include/utils.h"
#include "../include/dessin.h"

//libsdl-ttf2.0-0 libsdl-ttf2.0-dev
//gcc *.c -o graviter $(sdl2-config --cflags --libs) -lSDL-ttf -lm

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *rende = NULL;
    SDL_bool cont = SDL_TRUE;

    int nb;
    int masse;
    unsigned int frameLimit;
    Uint32 startTime;
    int frameCount;
    bool pause = true;

    if (argc != 3) {
        printf("Usage : %s <nb planetes> <masse planetes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    nb = atoi(argv[1]);
    masse = atoi(argv[2]);

    Planete* planete = init_planete(nb, masse);
    if(planete == NULL)
        sdl_exit("Erreur d'initialisation des planetes");

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        sdl_exit("Initiatlisation de la SDL");

    if(TTF_Init() != 0)
        sdl_exit("Erreur d'initialisation de la SDL_ttf");

    window = SDL_CreateWindow("Graviter simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    if(window == NULL)
        sdl_exit("Impossible de créer la fenètre");

    rende = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(rende == NULL)
        sdl_exit("Impossible de créer le rendue");

    frameLimit = SDL_GetTicks() + LIMIT;
    startTime = SDL_GetTicks();
    frameCount = 0;

    while(cont) {
        limit_fps(frameLimit);

        SDL_Event event;
        SDL_SetRenderDrawColor(rende, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rende);

        spawn_planete(planete, nb, rende);
        sdl_printf(rende, 10, 10, "Graviter simulator %s", !pause ? "(pause)" : "");
        show_fps(&frameCount, &startTime, rende);

        if (pause)
            update_planete(planete, nb);

        SDL_RenderPresent(rende);
        frameLimit = SDL_GetTicks() + LIMIT;

        while(SDL_PollEvent(&event))
            event_func(&cont, &event, &pause);
    }

    free(planete);
    SDL_DestroyRenderer(rende);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
