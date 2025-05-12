#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

int main(){

     
     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
          printf("Erreur SDL_Init: %s\n", SDL_GetError());
     }
     if (TTF_Init() == -1) {
          printf("Erreur TTF_Init: %s\n", TTF_GetError());
     }
     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
          printf("Erreur Mix_OpenAudio: %s\n", Mix_GetError());
     }

     SDL_Surface *ecran;
     ecran = SDL_SetVideoMode(1440,700,  32,SDL_HWSURFACE |SDL_DOUBLEBUF);
     int quitter =0;
     SDL_Event event;
     int indice_ecran=0;

     menu menu;
     init_menu(&menu);

     while(quitter==0){
         
         

                 switch(indice_ecran){
                   case 0:
                        
                        afficher_menu(menu,ecran,event);
                        SDL_Flip(ecran);

                       
                         while(SDL_PollEvent(&event)){

                                    switch(event.type){
                                          
                                           case SDL_QUIT:
                                                  quitter=1;
                                            break;

                                            case SDL_MOUSEBUTTONDOWN:
						if(event.button.button 		                                                   ==SDL_BUTTON_LEFT){
   
							if(menu.btn_select==5){
                                                                                                                        Mix_PlayChannel( -1, menu.son_click, 0 );
                                                               quitter=1;
                                                         }
                                                         if(menu.btn_select==1){
                                                                                                             Mix_PlayChannel( -1, menu.son_click, 0 );      
                                                           indice_ecran=1;
                                                         }
                                                         if(menu.btn_select==2){
                                                                                                                 Mix_PlayChannel( -1, menu.son_click, 0 );
                                                              indice_ecran=2;
                                                         }
                                                         if(menu.btn_select==3){
                                                      Mix_PlayChannel( -1, menu.son_click, 0 );
                                                             indice_ecran=3;
                                                         }
                                                         if(menu.btn_select==4){
                                                      Mix_PlayChannel( -1, menu.son_click, 0 );
                                                             indice_ecran=4;
                                                         }
                                                           if(menu.btn_select==6){
                                                      Mix_PlayChannel( -1, menu.son_click, 0 );
                                                             indice_ecran=6;
                                                         }
                                                 }break;

                                               case SDL_KEYDOWN:
                                                                                                
                                                   if(event.key.keysym.sym      							    ==SDLK_j){
Mix_PlayChannel( -1, menu.son_click, 0 );
                                                            indice_ecran=1;
                                                         }                                                       							   if(event.key.keysym.sym      							    ==SDLK_o){
Mix_PlayChannel( -1, menu.son_click, 0 );
                                                            indice_ecran=2;
                                                         }
                                                   if(event.key.keysym.sym      							    ==SDLK_m){
Mix_PlayChannel( -1, menu.son_click, 0 );
                                                            indice_ecran=3;
                                                         }
                                                   if(event.key.keysym.sym      							    ==SDLK_ESCAPE){
Mix_PlayChannel( -1, menu.son_click, 0 );
                                                            quitter=1;
                                                         }
                                            default:
                                                break;
                                     }
                        }
                         
                        mise_ajour_menu(&menu,event);

                       break;
                    case 1:
                           SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,    									0,0,0));
                           SDL_Flip(ecran);
                           while(SDL_PollEvent(&event)){

                                    switch(event.type){
                                          
                                           case SDL_QUIT:
                                                  quitter=1;
                                            break;
                                    }
                        }break;
                      case 2:
                           SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,    									0,0,0));
                           SDL_Flip(ecran);
                           while(SDL_PollEvent(&event)){

                                    switch(event.type){
                                          
                                           case SDL_QUIT:
                                                  quitter=1;
                                            break;
                                    }
                        }break;
                       case 3:
                           SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,    									0,0,0));
                           SDL_Flip(ecran);
                           while(SDL_PollEvent(&event)){

                                    switch(event.type){
                                          
                                           case SDL_QUIT:
                                                  quitter=1;
                                            break;
                                    }
                        }break;
                        case 4:
                           SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,    									0,0,0));
                           SDL_Flip(ecran);
                           while(SDL_PollEvent(&event)){

                                    switch(event.type){
                                          
                                           case SDL_QUIT:
                                                  quitter=1;
                                            break;
                                    }
                        }break;
 
                          case 5:
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_Flip(ecran);
    SDL_Delay(1000);
    quitter = 1;
    break;

			  case 6:
                           SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,    									0,0,0));
                           SDL_Flip(ecran);
                           while(SDL_PollEvent(&event)){

                                    switch(event.type){
                                          
                                           case SDL_QUIT:
                                                  quitter=1;
                                            break;
                                    }
                        }break;
                   default:
                      break;
                 }
        
    }
if (menu.backg != NULL) SDL_FreeSurface(menu.backg);
if (menu.jouer_btn[0] != NULL) SDL_FreeSurface(menu.jouer_btn[0]);
if (menu.jouer_btn[1] != NULL) SDL_FreeSurface(menu.jouer_btn[1]);
if (menu.option_btn[0] != NULL) SDL_FreeSurface(menu.option_btn[0]);
if (menu.option_btn[1] != NULL) SDL_FreeSurface(menu.option_btn[1]);
if (menu.score_btn[0] != NULL) SDL_FreeSurface(menu.score_btn[0]);
if (menu.score_btn[1] != NULL) SDL_FreeSurface(menu.score_btn[1]);
if (menu.hist_btn[0] != NULL) SDL_FreeSurface(menu.hist_btn[0]);
if (menu.hist_btn[1] != NULL) SDL_FreeSurface(menu.hist_btn[1]);
if (menu.quit_btn[0] != NULL) SDL_FreeSurface(menu.quit_btn[0]);
if (menu.quit_btn[1] != NULL) SDL_FreeSurface(menu.quit_btn[1]);
if (menu.reprendre_btn[0] != NULL) SDL_FreeSurface(menu.reprendre_btn[0]);
if (menu.reprendre_btn[1] != NULL) SDL_FreeSurface(menu.reprendre_btn[1]);
if (ecran != NULL) SDL_FreeSurface(ecran);
if (menu.logo != NULL) SDL_FreeSurface(menu.logo);
if (menu.Surface_Texte != NULL) SDL_FreeSurface(menu.Surface_Texte);

   
    TTF_CloseFont (menu.font);
    TTF_Quit();
    Mix_FreeMusic(menu.bg_music);
    Mix_CloseAudio();
    SDL_Quit();
 }    
     

