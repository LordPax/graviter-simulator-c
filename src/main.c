#include "../include/graviter.h"
#include "../include/utils.h"
#include "../include/dessin.h"
#include "../include/planete.h"

/**
 * @brief manage event
 *
 * @param cont determine if script continue or not
 * @param event sdl event to manage event
 * @param pause pause the "simulation"
 */
void event_func(
    SDL_bool *cont,
    SDL_Event *event,
    bool *pause,
    Camera *cam,
    Planete *planete,
    int nb,
    int masse,
    bool *show_info
) {
    static int mouse_x = 0;
    static int mouse_y = 0;
    static int cam_x = 0;
    static int cam_y = 0;

    switch (event->type) {
        case SDL_QUIT :
            *cont = SDL_FALSE;
            break;
        case SDL_KEYDOWN :
            switch(event->key.keysym.sym) {
                case SDLK_ESCAPE :
                    *cont = SDL_FALSE;
                    break;
                case SDLK_SPACE :
                    *pause = !(*pause);
                    break;
                case SDLK_a :
                    cam->x = 0;
                    cam->y = 0;
                    cam_x = 0;
                    cam_y = 0;
                    break;
                case SDLK_z :
                    *show_info = !(*show_info);
                    break;
                case SDLK_r :
                    planete = reinit_planete(planete, nb, masse);
                    if (planete == NULL)
                        sdl_exit("Erreur d'initialisation des planetes");
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN :
            if (event->button.button == SDL_BUTTON_LEFT) {
                mouse_x = event->button.x;
                mouse_y = event->button.y;
            }
            break;
        case SDL_MOUSEMOTION :
            if (event->button.button == SDL_BUTTON_LEFT) {
                cam->x = cam_x + event->motion.x - mouse_x;
                cam->y = cam_y + event->motion.y - mouse_y;
            }
            break;
        case SDL_MOUSEBUTTONUP :
            if (event->button.button == SDL_BUTTON_LEFT) {
                mouse_x = 0;
                mouse_y = 0;
                cam_x = cam->x;
                cam_y = cam->y;
            }
            break;
    }
}

int main(int argc, char **argv) {
    Camera cam = {0, 0};
    SDL_bool cont = SDL_TRUE;
    bool pause = false;
    bool show_info = false;
    int info_x = 10, info_y = 10;

    if (argc != 3) {
        printf("Usage : %s <nb planetes> <masse planetes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int nb = atoi(argv[1]);
    int masse = atoi(argv[2]);

    Planete* planete = init_planete(nb, masse);
    if (planete == NULL)
        sdl_exit("Erreur d'initialisation des planetes");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        sdl_exit("Initiatlisation de la SDL");

    if (TTF_Init() != 0)
        sdl_exit("Erreur d'initialisation de la SDL_ttf");

    SDL_Window *window = SDL_CreateWindow(
        "Graviter simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        W, H, 0
    );
    if (window == NULL)
        sdl_exit("Impossible de créer la fenètre");

    SDL_Renderer *rende = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (rende == NULL)
        sdl_exit("Impossible de créer le rendue");

    unsigned int frameLimit = SDL_GetTicks() + LIMIT;
    Uint32 startTime = SDL_GetTicks();
    int frameCount = 0;

    while (cont) {
        limit_fps(frameLimit);

        SDL_Event event;
        SDL_SetRenderDrawColor(rende, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rende);

        TextConf conf = {255, 255, 255, 255, 100, 25};
        sdl_printf(rende, conf, info_x, info_y, "Graviter simulator %s", pause ? "(pause)" : "");
        show_fps(rende, info_x, info_y + 25, &frameCount, &startTime);
        show_nb_planete(planete, info_x, info_y + 50, nb, rende);
        sdl_printf(rende, conf, info_x, info_y + 75, "Camera x: %d, y: %d", cam.x, cam.y);
        spawn_planete(planete, nb, rende, &cam, &show_info);

        if (!pause)
            update_planete(planete, nb);

        SDL_RenderPresent(rende);
        frameLimit = SDL_GetTicks() + LIMIT;

        while (SDL_PollEvent(&event))
            event_func(&cont, &event, &pause, &cam, planete, nb, masse, &show_info);
    }

    free(planete);
    SDL_DestroyRenderer(rende);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
