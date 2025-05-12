#include "menu.h"


void init_menu(menu *m)
{
     m->backg = IMG_Load("photo/Asset 12lll(1).png");   
     if(m->backg ==NULL){
          printf("erreur load background \n");
     }
    
    m->jouer_btn[0]=IMG_Load("photo/JOUER.png");
    m->jouer_btn[1]=IMG_Load("photo/JOUER2.png");

    m->option_btn[0]=IMG_Load("photo/OPTION.png");
    m->option_btn[1]=IMG_Load("photo/OPTION2.png");

    m->score_btn[0]=IMG_Load("photo/SCORE.png");
    m->score_btn[1]=IMG_Load("photo/SCORE2.png");

    m->hist_btn[0]=IMG_Load("photo/HISTOIRE.png");
    m->hist_btn[1]=IMG_Load("photo/HISTOIRE2.png");

    m->quit_btn[0]=IMG_Load("photo/QUITTER.png");
    m->quit_btn[1]=IMG_Load("photo/QUITTER2.png");

    m->reprendre_btn[0]=IMG_Load("photo/REPRENDRE.png");
    m->reprendre_btn[1]=IMG_Load("photo/REPRENDRE2.png");

    m->logo=IMG_Load("photo/logo.png");
    
    m->pos_btn_jouer.x=(1440/2) - (m->jouer_btn[0]->w/2);
    m->pos_btn_jouer.y=120;
    m->pos_btn_jouer.w=m->jouer_btn[0]->w;
    m->pos_btn_jouer.h=m->jouer_btn[0]->h;

    m->pos_btn_option.x=(1440/2) - (m->option_btn[0]->w/2);
    m->pos_btn_option.y=520;
    m->pos_btn_option.w=m->option_btn[0]->w;
    m->pos_btn_option.h=m->option_btn[0]->h;
    
    m->pos_btn_score.x=(1440/2) - (m->score_btn[0]->w/2);
    m->pos_btn_score.y=320;
    m->pos_btn_score.w=m->score_btn[0]->w;
    m->pos_btn_score.h=m->score_btn[0]->h;

    m->pos_btn_hist.x=(1440/2) - (m->hist_btn[0]->w/2);
    m->pos_btn_hist.y=420;
    m->pos_btn_hist.w=m->hist_btn[0]->w;
    m->pos_btn_hist.h=m->hist_btn[0]->h;

    m->pos_btn_quit.x=(1370- (m->quit_btn[0]->w +20));
    m->pos_btn_quit.y=(600- (m->quit_btn[0]->h +20));
    m->pos_btn_quit.w=m->quit_btn[0]->w;
    m->pos_btn_quit.h=m->quit_btn[0]->h;
    
    m->pos_btn_reprendre.x=(1440/2) - (m->reprendre_btn[0]->w/2);
    m->pos_btn_reprendre.y=220;
    m->pos_btn_reprendre.w=m->reprendre_btn[0]->w;
    m->pos_btn_reprendre.h=m->reprendre_btn[0]->h;

    m->bg_music = Mix_LoadMUS("Once Upon a Dream.mp3");
    if(m->bg_music ==NULL){
          printf("erreur load music \n");
     }else{
	Mix_PlayMusic(m->bg_music,-1);
     }
    
     m->son_click= Mix_LoadWAV( "CMPTKey_Souris_Converted.wav" );
     if(m->son_click ==NULL){
          printf("erreur load son click \n");
    }
    
    m->positiontext.w=m->positiontext.w;
    m->positiontext.h=m->positiontext.h;
    m->positiontext.x=(500);
    m->positiontext.y=40;

    m->pos_logo.w=m->pos_logo.w;
    m->pos_logo.h=m->pos_logo.h;
    m->pos_logo.x=900;
    m->pos_logo.y=50;

    m->textColor.r=0;
    m->textColor.g=0;
    m->textColor.b=128;
    m->font = TTF_OpenFont( "Quickstyler_PERSONAL_USE_ONLY.otf", 60 );
    
}



void afficher_menu(menu m,SDL_Surface *ecran,SDL_Event event)
{ 
     
     SDL_BlitSurface(m.backg,NULL,ecran,NULL);
     
     if(touche_souris(m.pos_btn_jouer,event)==0){
     	SDL_BlitSurface(m.jouer_btn[0],NULL,ecran,&m.pos_btn_jouer);
     }else{
	SDL_BlitSurface(m.jouer_btn[1],NULL,ecran,&m.pos_btn_jouer);
     }

     if(touche_souris(m.pos_btn_option,event)==0){
     	SDL_BlitSurface(m.option_btn[0],NULL,ecran,&m.pos_btn_option);
     }else{
	SDL_BlitSurface(m.option_btn[1],NULL,ecran,&m.pos_btn_option);
     }

     if(touche_souris(m.pos_btn_score,event)==0){	
	SDL_BlitSurface(m.score_btn[0],NULL,ecran,&m.pos_btn_score);
     }else{
	SDL_BlitSurface(m.score_btn[1],NULL,ecran,&m.pos_btn_score);
     }

     if(touche_souris(m.pos_btn_hist,event)==0){
     	SDL_BlitSurface(m.hist_btn[0],NULL,ecran,&m.pos_btn_hist);
     }else{
	SDL_BlitSurface(m.hist_btn[1],NULL,ecran,&m.pos_btn_hist);
      }

      if(touche_souris(m.pos_btn_quit,event)==0){
     	SDL_BlitSurface(m.quit_btn[0],NULL,ecran,&m.pos_btn_quit);
     }else{
	SDL_BlitSurface(m.quit_btn[1],NULL,ecran,&m.pos_btn_quit);
     }


      if(touche_souris(m.pos_btn_reprendre,event)==0){
     	SDL_BlitSurface(m.reprendre_btn[0],NULL,ecran,&m.pos_btn_reprendre);
     }else{
	SDL_BlitSurface(m.reprendre_btn[1],NULL,ecran,&m.pos_btn_reprendre);
     }
    
    m.Surface_Texte = TTF_RenderText_Blended (m.font, "SNOW 'S FLAME", m.textColor );
    SDL_BlitSurface(m.Surface_Texte, NULL, ecran, &m.positiontext);
    SDL_BlitSurface(m.logo,NULL,ecran,&m.pos_logo);
}




int touche_souris(SDL_Rect pos_btn,SDL_Event event)
{
	if( event.type==SDL_MOUSEMOTION){
		if(event.motion.x>=pos_btn.x && event.motion.x<=pos_btn.x+pos_btn.w &&
event.motion.y>=pos_btn.y&& event.motion.y<=pos_btn.y+pos_btn.h){
                  return 1;
               }
                else{
                    return 0;
                }
     }
 return 0;
}

void mise_ajour_menu(menu *m,SDL_Event event)
{
     if(touche_souris(m->pos_btn_jouer,event)==1){
	m->btn_select=1;
     }
     else if(touche_souris(m->pos_btn_option,event)==1){
	m->btn_select=2;
     }
     else if(touche_souris(m->pos_btn_score,event)==1){
	m->btn_select=3;
     }
     else if(touche_souris(m->pos_btn_hist,event)==1){
	m->btn_select=4;
     } 
     else if(touche_souris(m->pos_btn_quit,event)==1){
	m->btn_select=5;
     } 
     else if(touche_souris(m->pos_btn_reprendre,event)==1){
	m->btn_select=6;
     } 
     else {
	m->btn_select=0;
   }
    
}

