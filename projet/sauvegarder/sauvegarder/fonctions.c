#include "fonction.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
bool button_yes_clicked = false;
SDL_Surface *button_yes_hover = NULL; 
bool hover_yes = false;  
bool button_no_clicked = false;
SDL_Surface *button_no_hover = NULL; 
bool hover_no = false; 
bool button_load_clicked = false;
SDL_Surface *button_load_hover = NULL; 
SDL_Surface *background_third = NULL;
bool hover_load = false;
bool button_new_clicked = false;
SDL_Surface *button_new_hover = NULL; 
bool hover_new = false;
void init_SDL();
void init_SDL() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    screen = SDL_SetVideoMode(1440,700, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("Menu de Sauvegarde", NULL);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}
extern SDL_Surface *button_yes_hover;
extern SDL_Surface *button_no_hover;
extern SDL_Surface *button_load_hover;
extern SDL_Surface *button_new_hover;
extern bool button_yes_clicked;
extern bool button_no_clicked;
extern bool button_load_clicked;
extern bool button_new_clicked;
extern TTF_Font *font;
void load_assets() {

background_third = IMG_Load("final_resized_1440x700.png");

    background = IMG_Load("final_resized_1440x700.png");
    background_new = IMG_Load("final.png");
    button_yes = IMG_Load("yes11.png");
    button_yes_hover = IMG_Load("yes22.png");
    button_no = IMG_Load("no11.png");
    button_no_hover= IMG_Load("no22.png");
    button_load = IMG_Load("Fichier2.png");
    button_load_hover = IMG_Load("Fichier1.png");
    button_new = IMG_Load("nouvelle11.png");
    button_new_hover = IMG_Load("nouvelle22.png");
    music = Mix_LoadMUS("sonn.mp3");
    hover_sound = Mix_LoadWAV("s.wav");
}

void handle_events(bool *running, bool *show_options, bool *show_second_window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_n) {
                    printf("Touche 'N' pressée\n");
                    show_third_window = true;
                }
                break;

            case SDL_MOUSEMOTION:
                
                if (event.motion.x >= pos_yes.x && event.motion.x <= pos_yes.x + button_yes->w &&
                    event.motion.y >= pos_yes.y && event.motion.y <= pos_yes.y + button_yes->h) {
                    if (!hover_yes) {
                        hover_yes = true;  
                        Mix_PlayChannel(-1, hover_sound, 0);
                    }
                } else {
                    hover_yes = false; 
                }

                if (event.motion.x >= pos_no.x && event.motion.x <= pos_no.x + button_no->w &&
                    event.motion.y >= pos_no.y && event.motion.y <= pos_no.y + button_no->h) {
                    if (!hover_no) {
                        hover_no = true;
                        Mix_PlayChannel(-1, hover_sound, 0);
                    }
                } else {
                    hover_no = false;
                }

               
                if (*show_second_window) {
                    if (event.motion.x >= pos_load.x && event.motion.x <= pos_load.x + button_load->w &&
                        event.motion.y >= pos_load.y && event.motion.y <= pos_load.y + button_load->h) {
                        if (!hover_load) {
                            hover_load = true;
                            Mix_PlayChannel(-1, hover_sound, 0);
                        }
                    } else {
                        hover_load = false;
                    }

                    if (event.motion.x >= pos_new.x && event.motion.x <= pos_new.x + button_new->w &&
                        event.motion.y >= pos_new.y && event.motion.y <= pos_new.y + button_new->h) {
                        if (!hover_new) {
                            hover_new = true;
                            Mix_PlayChannel(-1, hover_sound, 0);
                        }
                    } else {
                        hover_new = false;
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    
                    if (!*show_second_window) {
                        if (event.button.x >= pos_yes.x && event.button.x <= pos_yes.x + button_yes->w &&
                            event.button.y >= pos_yes.y && event.button.y <= pos_yes.y + button_yes->h) {
                            button_yes_clicked = true;
                            button_no_clicked = true;
                            button_load_clicked = true;
                            button_new_clicked = true;
                            *show_second_window = true;  
                            printf("show_second_window = %d\n", *show_second_window);
                        }
                    }

                   
                    if (event.button.x >= pos_no.x && event.button.x <= pos_no.x + button_no->w &&
                        event.button.y >= pos_no.y && event.button.y <= pos_no.y + button_no->h) {
                        *running = false;  
                    }

         
                    if (*show_second_window) {
                       
                        if (event.button.x >= pos_load.x && event.button.x <= pos_load.x + button_load->w &&
                            event.button.y >= pos_load.y && event.button.y <= pos_load.y + button_load->h) {
                            printf("Chargement du jeu...\n");
                            
                        }

                       
                        if (event.button.x >= pos_new.x && event.button.x <= pos_new.x + button_new->w &&
                            event.button.y >= pos_new.y && event.button.y <= pos_new.y + button_new->h) {
                            printf("Nouvelle partie...\n");
                            show_third_window = true;
                            
                        }
                    }
                }
                break;
        }
    }
}


extern SDL_Surface *surfaceTexte;
void render(bool show_options, bool show_second_window) {
if (show_third_window) {
    SDL_BlitSurface(background_third, NULL, screen, NULL);}
else
    if (show_second_window) {
        
        SDL_BlitSurface(background_new, NULL, screen, NULL);
        SDL_BlitSurface(hover_load ? button_load_hover : button_load, NULL, screen, &pos_load);
        SDL_BlitSurface(hover_new ? button_new_hover : button_new, NULL, screen, &pos_new);
 SDL_Flip(screen);   } else {
        
        SDL_BlitSurface(background, NULL, screen, NULL);
        
        SDL_Color textColor = {255,255,255};
        surfaceTexte = TTF_RenderText_Solid(font, "Voulez-vous sauvegarder votre jeu?", textColor);
        if (surfaceTexte) {
            SDL_Rect textPos;
            textPos.x = SCREEN_WIDTH / 9;
            textPos.y = SCREEN_HEIGHT / 4;
            textPos.w = surfaceTexte->w * 2;
            textPos.h = surfaceTexte->h * 2;
            SDL_BlitSurface(surfaceTexte, NULL, screen, &textPos);
        }
SDL_BlitSurface(hover_yes ? button_yes_hover : button_yes, NULL, screen, &pos_yes);
SDL_BlitSurface(hover_no ? button_no_hover : button_no, NULL, screen, &pos_no);
    }
    SDL_Flip(screen);  
}
