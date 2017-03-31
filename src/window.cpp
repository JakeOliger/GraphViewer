#include "window.h"

Window::Window(int width, int height, bool center = true, const char title[] = "Default Title")
{
	this->width = width;
	this->height = height;

	window = NULL;
	renderer = NULL;

	int windowPos = center ? SDL_WINDOWPOS_CENTERED : SDL_WINDOWPOS_UNDEFINED;

	window = SDL_CreateWindow(title, windowPos, windowPos, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window() {
	SDL_DestroyWindow(window);
	renderer = NULL;
}

bool Window::isInitialized() {
	return window != NULL && renderer != NULL;
}

void Window::clear(int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
}

void Window::update() {
	SDL_RenderPresent(renderer);
}
