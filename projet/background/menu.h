#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define MAX_PSEUDO_LEN 20
#define NB_MEILLEURS_SCORES 3

// Structure pour la gestion du pseudo et score courant
typedef struct {
    SDL_Surface *back;                   // Arrière-plan
    SDL_Surface *valider_btt[2];         // Bouton "Valider" [normal, appuyé]
    SDL_Rect pos_valider;                // Position du bouton "Valider"
    SDL_Rect pos_texte;                  // Position du texte de saisie

    TTF_Font *font;                      // Police d'écriture
    SDL_Color textColor;                 // Couleur du texte
    SDL_Surface *texte;                  // Surface pour le texte du pseudo

    char pseudo[MAX_PSEUDO_LEN];         // Saisie du pseudo
    int score;                           // Score du joueur courant
    int parties_jouees;                  // Compteur de parties jouées
} score;

// Structure pour stocker un score parmi les meilleurs
typedef struct {
    char pseudo[MAX_PSEUDO_LEN];
    int score;
} MeilleurScore;

// Initialise la structure score (images, bouton, police, etc.)
void init_score(score *s);

// Gère la saisie clavier et le clic sur le bouton "Valider"
void gerer_evenements(score *s, SDL_Surface *ecran, int *mode, int *running);

// Affiche l’écran de saisie du pseudo avec le bouton "Valider"
void afficher(score *s, SDL_Surface *ecran, int mode, int *running);

// Ajoute un score dans le tableau top[] et le trie (du plus grand au plus petit)
void ajouter_score(MeilleurScore *top, int *nb_scores, const char *pseudo, int score);


void afficher_resultat(SDL_Surface *screen, SDL_Surface *result_bg, TTF_Font *font, const char *pseudo, int score);
void afficher_meilleurs_scores_fenetre(SDL_Surface *screen, MeilleurScore top[], int nb_scores, SDL_Surface *etoiles[], TTF_Font *font);
 

#endif // MENU_H

