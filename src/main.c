#include "../include/graviter.h"

//libsdl-ttf2.0-0 libsdl-ttf2.0-dev
//gcc *.c -o graviter $(sdl2-config --cflags --libs) -lSDL-ttf -lm

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *rende = NULL;
    SDL_bool cont = SDL_TRUE;

    int nb;
    int masse;
    unsigned int frameLimit;
    _Bool pause = true;

    if (argc != 3)
        exit(0);

    nb = atoi(argv[1]);
    masse = atoi(argv[2]);
    printf("Graviter : nombre de planetes : %d\n", nb);
    printf("Graviter : masse de chaque planete : %d\n", masse);

    Planete *planete = malloc(sizeof(Planete) * nb); // initialisation des planetes

    if(planete == NULL)
        exit(1);

    Init_Planete(planete, nb, masse);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) // lancer SDL
        SDL_Exit("Initiatlisation de la SDL");

    window = SDL_CreateWindow("Graviter simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    if(window == NULL)
        SDL_Exit("Impossible de créer la fenètre");

    rende = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(rende == NULL)
        SDL_Exit("Impossible de créer le rendue");

    frameLimit = SDL_GetTicks() + LIMIT;

    while(cont) {
        limitFps(frameLimit);

        SDL_Event event;
        SDL_SetRenderDrawColor(rende, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rende);

        Spawn_Planete(planete, nb, rende);

        if(pause)
            for (int i = 0; i < nb; ++i)
                if(planete[i].exist)
                    Update_Planete(&planete[i], planete, nb);

        SDL_RenderPresent(rende);
        frameLimit = SDL_GetTicks() + LIMIT;

        while(SDL_PollEvent(&event))
            eventFunc(&cont, &event, &pause);
    }

    free(planete);
    SDL_DestroyRenderer(rende);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS; //return 0;
}
