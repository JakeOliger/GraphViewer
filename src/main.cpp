// Standard library
#include <cmath>
#include <complex>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Third party
#include "SDL.h"

// Our files
#include "window.h"

using namespace std::complex_literals;

Window *window = NULL;

int width = 1600;
int height = 900;

bool init() {
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize! Error: %s\n", SDL_GetError());
		success = false;
	}
	
	// Initialize the window
	window = new Window(width, height, true, "Mandelbrot Set");
	if (!window->isInitialized()) {
		printf("Window failed to initialize! Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

double f(double x) {
	return      (x * x * x * x * x * x
		- 2   * x * x * x * x * x
		- 26  * x * x * x * x
		+ 28  * x * x * x
		+ 145 * x * x
		- 26  * x
		- 80) / 100.0;
}

// Main program loop
int main(int argc, char* args[]) {
	if (init() == false) {
		return -1;
	}

	SDL_Renderer *renderer = window->getRenderer();
	SDL_Event ev;

	bool pause = false;
	bool quit = false;

	int originX = width / 2;
	int originY = height / 2;
	double scale = 1.0 / 20.0;
	double detail = 0.05;
	int notchLength = 5;

	while (!quit) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) { // The 'X' button
				quit = true;
			} else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
					case SDLK_ESCAPE: // Press escape to quit simulation
						quit = true;
						break;
					case SDLK_SPACE: // Press space to pause simulation
						pause = !pause;
						break;
					case SDLK_UP:
						originY += 50;
						break;
					case SDLK_DOWN:
						originY -= 50;
						break;
					case SDLK_LEFT:
						originX += 50;
						break;
					case SDLK_RIGHT:
						originX -= 50;
						break;
				}
			}
		}

		if (!pause) {
			window->clear(228, 214, 167);

			SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
			
			// Y Axis
			SDL_RenderDrawLine(renderer, originX, 0, originX, height);
			// X Axis
			SDL_RenderDrawLine(renderer, 0, originY, width, originY);

			// Notch at each x % 1 == 0 position
			for (double i = -width * scale; i < width * scale; i += 1) {
				int tx = originX + i / scale;
				SDL_RenderDrawLine(renderer, tx, originY - notchLength, tx, originY + notchLength);
			}
			for (double i = -height * scale; i < height * scale; i += 1) {
				int ty = originY + i / scale;
				SDL_RenderDrawLine(renderer, originX - notchLength, ty, originX + notchLength, ty);
			}

			std::vector<int> xCoords;
			std::vector<int> yCoords;
			
			int lastX = -originX * scale;
			int lastY = -(f(lastX) - originY * scale) / scale;

			SDL_SetRenderDrawColor(renderer, 28, 17, 10, 255);
			for (double x = -originX * scale; x < width; x += detail) {
				int dx = (x + originX * scale) / scale;
				int dy = -((f(x) - originY * scale) / scale);

				// Draw big dots on x % 1 == 0 spots
				if (x - floor(x) > 1 - detail) { // This 1-detail business... floating point
					xCoords.push_back(dx);
					yCoords.push_back(dy);
				}
				
				SDL_RenderDrawLine(renderer, lastX, lastY, dx, dy);

				lastX = dx;
				lastY = dy;
			}

			SDL_SetRenderDrawColor(renderer, 155, 41, 21, 255);
			for (unsigned int i = 0; i < xCoords.size(); i++) {
				SDL_Rect rect;
				rect.x = xCoords.at(i) - 2;
				rect.y = yCoords.at(i) - 2;
				rect.w = 5;
				rect.h = 5;
				SDL_RenderFillRect(renderer, &rect);
			}

			window->update();
		}
	}

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}
