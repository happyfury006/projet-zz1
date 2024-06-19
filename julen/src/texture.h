#ifndef texture_h
#define texture_h

// void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_with_texture_3(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* load_texture_from_image(char * file_image_name, SDL_Window * window, SDL_Renderer * renderer);

#endif