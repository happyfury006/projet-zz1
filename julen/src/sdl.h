#ifndef sdl_h
#define sdl_h

#include <SDL2/SDL.h>
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
void drawRect(SDL_Renderer* renderer, int x, int y);
SDL_Window* creationwindow(const char* title, int x, int y, int w, int h);
#endif