#include <SDL.h>
#include <vector>
#include <iostream>
#include <cstdint>

#undef main
 
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;  

struct Vec3 {
	float x, y, z;
	Vec3 operator-(const Vec3& o) const {
		return { x - o.x, y - o.y, z - o.z };
	}
	Vec3 operator+(const Vec3& o) const {
		return { x + o.x, y + o.y, z + o.z }; 
	}
	Vec3 operator*(const Vec3& o) const {
		return { x * o.x, y * o.y, z * o.z };

	
	}
};

struct Mat4 {
	float m[4][4] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

};

Vec3 MultiplyMatrixVec3(const Mat4& mat, const Vec3& v) {
	float x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.z * mat.m[0][2] + mat.m[0][3];
	float y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.z * mat.m[1][2] + mat.m[1][3];
	float z = v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.z * mat.m[2][2] + mat.m[2][3];

	return { x, y, z };
};


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

		for (int y = centerY - 30; y <= centerY + 30; ++y) {
			for (int x = centerX - 30; x <= centerX + 30; ++x) {
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