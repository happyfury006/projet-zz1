// #include <SDL2/SDL_image.h>
#ifndef sprite_h
#define sprite_h

// void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
// void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
// SDL_Texture* load_texture_from_image(char * file_image_name, SDL_Window * window, SDL_Renderer * renderer);
void animationparallax(SDL_Texture* bg_texture, SDL_Texture* anakin_texture,SDL_Texture* sebulba_texture,SDL_Texture* destroyer_texture, SDL_Window* window, SDL_Renderer* renderer);


#endif