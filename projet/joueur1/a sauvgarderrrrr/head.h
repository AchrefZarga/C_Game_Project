#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

// Structure pour représenter un personnage
typedef struct {
    SDL_Surface *spriteSheet;  // Sprite sheet du personnage
    SDL_Rect posScreen;        // Position sur l'écran
    SDL_Rect posSprite;        // Partie visible du sprite sheet
    int direction;             // Direction actuelle (gauche, droite, etc.)
    int currentAction;         // Action actuelle (marcher, sauter, etc.)
    int currentFrame;          // Indice de la frame courante dans l'animation
    int vies;                  // Nombre de vies restantes
    int score;                 // Score du joueur
    bool estMort;              // Indicateur si le personnage est mort
    SDL_Surface *imagesVies[4]; // Images représentant les vies (3, 2, 1, 0)
} Personnage;

// Structure pour le sous-menu joueur
typedef struct {
    SDL_Surface *background;

    // Boutons du menu principal
    SDL_Surface *mono_btn[2];
    SDL_Surface *multi_btn[2];
    SDL_Surface *retour_btn[2];

    // Boutons du sous-menu
    SDL_Surface *avatar1_btn[2];
    SDL_Surface *avatar2_btn[2];
    SDL_Surface *input1_btn[2];
    SDL_Surface *input2_btn[2];
    SDL_Surface *valider_btn[2];
    SDL_Surface *retrn_btn[2];

    // Positions des boutons
    SDL_Rect pos_btn_mono;
    SDL_Rect pos_btn_multi;
    SDL_Rect pos_btn_retour;

    SDL_Rect pos_btn_avatar1;
    SDL_Rect pos_btn_avatar2;
    SDL_Rect pos_btn_input1;
    SDL_Rect pos_btn_input2;
    SDL_Rect pos_btn_valider;
    SDL_Rect pos_btn_retrn;

    // Musique et sons
    Mix_Music *bg_music;
    Mix_Chunk *hover_sound;

    // Informations de l'état
    int avatar_selectionne; // 0: Aucun, 1: Avatar 1, 2: Avatar 2
    int input_selectionne;  // 0: Aucun, 1: Jouer avec le clavier
} sous_menu_joueur;

// Prototypes des fonctions du menu
void init_sous_menu_joueur(sous_menu_joueur *sm);
void afficher_interface_principale(sous_menu_joueur *sm, SDL_Surface *ecran, SDL_Event event, int *indice_ecran, int *quitter);
void afficher_interface_secondaire(sous_menu_joueur *sm, SDL_Surface *ecran, SDL_Event event, int *indice_ecran, int *quitter);
int touche_souris(SDL_Rect pos_btn, SDL_Event event);

// Prototypes des fonctions du jeu
void initialiserPersonnage(Personnage *perso, const char *spritePath, int startX, int startY);
void animerPersonnage(Personnage *perso);
void deplacerPersonnage(Personnage *perso, const int *inputStates, int haut, int bas, int gauche, int droite, int action);
void afficherPersonnage(SDL_Surface *ecran, Personnage *perso, SDL_Rect *camera);
void afficherVies(SDL_Surface *ecran, Personnage *perso, int x, int y);
void verifierToucher(Personnage *perso, SDL_Rect *obstacles, int nbObstacles);
void jeuMono(SDL_Surface *ecran, int avatar_selectionne);
void jeuMulti(SDL_Surface *ecran);

#endif

