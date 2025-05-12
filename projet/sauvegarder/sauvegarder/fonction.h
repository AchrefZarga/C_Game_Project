#ifndef FONCTION_H
#define FONCTION_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 700

extern SDL_Surface *background;  
extern SDL_Surface *button_yes;  
extern SDL_Surface *button_load;
extern SDL_Surface *button_new;
extern SDL_Surface *surfaceTexte;
extern SDL_Surface *screen, *background, *button_yes, *button_no;
extern SDL_Surface *button_load, *button_new, *background_new;
extern SDL_Rect pos_yes, pos_no, pos_load, pos_new;
extern Mix_Music *music;
extern Mix_Chunk *hover_sound;
extern bool button_yes_clicked;
extern bool button_no_clicked;
extern SDL_Surface *button_yes_hover;
extern bool hover_yes;
extern SDL_Surface *button_no_hover;
extern bool hover_no;
extern SDL_Surface *button_load_hover;
extern bool hover_load;
extern SDL_Surface *button_new_hover;
extern bool hover_new;
extern bool show_new_background;
extern SDL_Surface *background_third;
extern bool show_third_window;

SDL_Color textColor;
void init_SDL();
void load_assets(); 
void handle_events(bool *running, bool *show_options, bool *show_second_window) ;
void render(bool show_options, bool show_second_window) ;
void free_resources();
#endif /* FONCTION_H */
