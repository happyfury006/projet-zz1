#ifndef xwindow_h
#define xwindow_h
void SDL_SetWindowPosition(SDL_Window * window, int x, int y);
void SDL_GetWindowPosition(SDL_Window * window,int *x, int *y);
int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);
// SDL_Window* creationwindow(const char* title, int x, int y, int w, int h);
int mainxwindow(int argc, char** argv);
#endif