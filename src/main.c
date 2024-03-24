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

    Planete* planete = Init_Planete(nb, masse);
    if(planete == NULL)
        SDL_Exit("Erreur d'initialisation des planetes");

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        SDL_Exit("Initiatlisation de la SDL");

    if(TTF_Init() != 0)
        SDL_Exit("Erreur d'initialisation de la SDL_ttf");

    window = SDL_CreateWindow("Graviter simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    if(window == NULL)
        SDL_Exit("Impossible de créer la fenètre");

    rende = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(rende == NULL)
        SDL_Exit("Impossible de créer le rendue");

    frameLimit = SDL_GetTicks() + LIMIT;
    startTime = SDL_GetTicks();
    frameCount = 0;

    while(cont) {
        limitFps(frameLimit);

        SDL_Event event;
        SDL_SetRenderDrawColor(rende, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rende);

        Spawn_Planete(planete, nb, rende);
        drawText(10, 10, "Graviter simulator", rende);
        show_fps(&frameCount, &startTime, rende);

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
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
