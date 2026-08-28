#include <SDL.h>
#include <vector>
#include <iostream>
#include <cstdint>

#undef main
 
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;  

int main(int argc, char* argv[]) {
    bool isRunning = true;
    SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "BOY BOY it didnt work!  " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Silly little renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cerr << "son son WINDOW DIDNT WORK! " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	std::vector<uint32_t> pixelBuffer(SCREEN_WIDTH * SCREEN_HEIGHT, 0xFF000000);

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }


		std::fill(pixelBuffer.begin(), pixelBuffer.end(), 0xFF1E1E1E);



		int centerX = SCREEN_WIDTH / 2;
		int centerY = SCREEN_HEIGHT / 2;

		for (int y = centerY - 10; y <= centerY + 10; ++y) {
			for (int x = centerX - 10; x <= centerX + 10; ++x) {
				pixelBuffer[y * SCREEN_WIDTH + x] = 0xFF36013F;
			}
		}

		SDL_UpdateTexture(texture, nullptr, pixelBuffer.data(), SCREEN_WIDTH * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
    }
	

	return 0;
}