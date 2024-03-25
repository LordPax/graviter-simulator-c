#include "../include/graviter.h"
#include "../include/utils.h"

/**
 * @brief exit from SDL
 *
 * @param msg message to show when exiting
 */
void sdl_exit(const char *msg) {
    SDL_Log("Erreur : %s > %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/**
 * @brief limit fps
 *
 * @param limit time of frame in ms
 */
void limit_fps(unsigned int limit) {
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
        return;
    else if(limit > ticks + LIMIT)
        SDL_Delay(LIMIT);
    else
        SDL_Delay(limit - ticks);
}

/**
 * @brief calculate fps
 *
 * @param frameCount count of frame
 * @param lastFrameTime time of last frame
 * @return fps
 */
int calculate_fps(int* frameCount, Uint32* lastFrameTime) {
    Uint32 currentFrameTime = SDL_GetTicks();
    static int fps;
    int diff = currentFrameTime - *lastFrameTime;

    (*frameCount)++;

    if (diff >= 1000) {
        fps = *frameCount;
        *frameCount = 0;
        *lastFrameTime = currentFrameTime;
    }

    return fps;
}

