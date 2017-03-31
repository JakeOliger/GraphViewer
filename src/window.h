#ifndef __window_h__
#define __window_h__

#include "SDL.h"

class Window {
public:
	Window(int width, int height, bool center, const char title[]);
	~Window();

	SDL_Renderer *getRenderer() { return renderer; }

	bool isInitialized();
	void clear(int r = 0, int g = 0, int b = 0);
	void update();
private:
	int height;	// Window height (in px)
	int width;	// Window width (in px)

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif // __window_h__
