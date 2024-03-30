#include "../include/graviter.h"

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
    Camera *cam
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
