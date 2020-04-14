#include <stdlib.h>
#include <iostream>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600
#define SCALE 10
double deltaTime = 0;
SDL_Renderer *renderer;

class Particle {
	public:
		Particle(float x, float y);
		void update();
		void draw();
		float X=0;
		float Y=0;
		float xVel=0;
		float yVel=0;
};

Particle::Particle(float x, float y) {
	X = x;
	Y = y;
}

void Particle::update() {
	if(Y<(WINDOW_WIDTH/SCALE)-2) yVel += 0.000981;
	else yVel *= -0.9;

	Y+=yVel;
}

void Particle::draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawPoint(renderer, X, Y);
}

Uint64 NOW = 0;
Uint64 LAST = 0;

using namespace std;

int main(void) {
    SDL_Event event;
    SDL_Window *window;
    float x=0;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
		SDL_RenderSetScale(renderer,SCALE,SCALE);

		Particle water1 = Particle(8,0);
		Particle water2 = Particle(14,4);

    while (1) {

			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();

			deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
			if(deltaTime > 100) deltaTime = 0;

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			// Fill the screen with the colour
			water1.update();
			water2.update();
			water1.draw();
			water2.draw();
			//SDL_RenderClear(renderer);

			//x+=deltaTime/100;

			//for(int i = 0; i < x; i++)
			//	SDL_RenderDrawPoint(renderer, i, 0);

			SDL_RenderPresent(renderer);
      if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;

			SDL_Delay(100/60);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
