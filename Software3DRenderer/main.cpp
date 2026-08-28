#include <SDL.h>
#include <vector>
#include <iostream>
#include <cstdint>



int main() {
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
    }
	return 0;
}