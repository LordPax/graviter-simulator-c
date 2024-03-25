#include "../include/graviter.h"

/**
 * @brief manage event
 *
 * @param cont determine if script continue or not
 * @param event sdl event to manage event
 * @param pause pause the "simulation"
 */
void event_func(SDL_bool *cont, SDL_Event *event, bool *pause) {
    switch(event->type) {
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
            }
            break;
    }
}
