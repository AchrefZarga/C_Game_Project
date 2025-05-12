#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "fonction.h"
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 700
SDL_Surface *surfaceTexte = NULL;
SDL_Surface *screen = NULL, *background = NULL, *button_yes = NULL, *button_no = NULL;
SDL_Surface *button_load = NULL, *button_new = NULL, *background_new = NULL;
SDL_Rect pos_yes, pos_no, pos_load, pos_new;
Mix_Music *music = NULL;
Mix_Chunk *hover_sound = NULL;
TTF_Font *font = NULL;

bool show_new_background = false;
bool show_third_window = false;

int main(int argc, char *argv[]) {


    bool running = true;
    bool show_options = false;
    bool button_yes_clicked = false; 
    bool hover_yes = false; 
    bool hover_no = false; 
    bool hover_load = false;
    bool hover_new = false;
    bool show_second_window = false; 

    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur d'initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 2048) < 0) {
        printf("Erreur d'initialisation SDL_mixer : %s\n", Mix_GetError());
        return 1;
    }
Mix_AllocateChannels(16);

    font = TTF_OpenFont("arial.ttf", 45);
    if (!font) {
        printf("Erreur d'initialisation SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }
load_assets();  

    Mix_PlayMusic(music, -1);

    init_SDL();
    load_assets();

    SDL_Color textColor = {0, 0, 0};

    pos_yes.x = SCREEN_WIDTH / 5 - button_yes->w / 2;
    pos_yes.y = SCREEN_HEIGHT / 2.5;
    pos_no.x = 3 * SCREEN_WIDTH / 6 - button_no->w / 2;
    pos_no.y = SCREEN_HEIGHT / 2.5;

    pos_load.x = SCREEN_WIDTH / 3 - button_load->w / 2;
    pos_load.y = SCREEN_HEIGHT / 3 - 50;
    pos_new.x = SCREEN_WIDTH / 3 - button_new->w / 2;
    pos_new.y = SCREEN_HEIGHT / 3 + 50;

while (running) {
    if (!show_second_window) {
        handle_events(&running, &show_options, &show_second_window);
 
    } else {
        handle_events(&running, &show_options, &show_second_window);
 
    }
    render(show_options, show_second_window);
 
    SDL_Delay(16);
}


    SDL_FreeSurface(background);
    SDL_FreeSurface(background_new);
SDL_FreeSurface(background_third);
    SDL_FreeSurface(button_yes);
    SDL_FreeSurface(button_no);
    SDL_FreeSurface(button_load);
    SDL_FreeSurface(button_new);
    SDL_FreeSurface(surfaceTexte);
    Mix_FreeMusic(music);
    Mix_FreeChunk(hover_sound);
    Mix_CloseAudio();
    TTF_CloseFont(font);

    SDL_Quit();

    return 0;
}
