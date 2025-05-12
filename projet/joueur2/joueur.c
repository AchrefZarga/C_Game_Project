#include "joueur.h"
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>

void initJoueur(Joueur* j, const char* spritePath, int x, int y) {
    j->spriteSheet = IMG_Load(spritePath);
    if (!j->spriteSheet) {
        fprintf(stderr, "Erreur de chargement du sprite: %s\n", IMG_GetError());
        return;
    }

    j->positionEcran.x = x;
    j->positionEcran.y = y;
    j->positionEcran.w = LARGEUR_FRAME;
    j->positionEcran.h = HAUTEUR_FRAME;

    j->frameActuel.x = 0;
    j->frameActuel.y = 0;
    j->frameActuel.w = LARGEUR_FRAME;
    j->frameActuel.h = HAUTEUR_FRAME;

    j->animation = ANIM_IDLE;
    j->direction = 0;
    j->frameIndex = 0;
    j->derniereAnimation = 0;
    j->vies = 3;
    j->score = 0;
    j->estActif = true;
    j->auSol = true;
    j->enSaut = false;
    initCoeurs(j);
}

void animerJoueur(Joueur* j) {
    Uint32 maintenant = SDL_GetTicks();
    if (maintenant > j->derniereAnimation + 140) {
        if (j->animation == ANIM_SAUT || j->animation == ANIM_ATTAQUE) {
            if (j->frameIndex < NB_FRAMES - 1) {
                j->frameIndex++;
            } else {
                j->animation = ANIM_IDLE;
                j->frameIndex = 0;
            }
        } else if (j->animation == ANIM_MARCHE) {
            j->frameIndex = (j->frameIndex + 1) % NB_FRAMES;
        } else if (j->animation == ANIM_MORT) {
            if (j->frameIndex < NB_FRAMES - 1) {
                j->frameIndex++;
            } else {
                j->frameIndex = NB_FRAMES - 1; // Stopper sur la dernière frame
            }
        } else if (j->animation == ANIM_GAGNER) {
            // Animation de victoire : soit en boucle, soit stop sur la dernière frame
            if (j->frameIndex < NB_FRAMES - 1) {
                j->frameIndex++;
            } else {
                j->frameIndex = 0; // Boucle (ou garder NB_FRAMES - 1 pour rester sur la dernière frame)
            }
        }

        j->frameActuel.x = j->frameIndex * LARGEUR_FRAME;

        // Choisir la ligne du sprite en fonction de l'animation
        if (j->animation == ANIM_MARCHE) {
            j->frameActuel.y = 0 * HAUTEUR_FRAME;
        } else if (j->animation == ANIM_SAUT) {
            j->frameActuel.y = 1 * HAUTEUR_FRAME;
        } else if (j->animation == ANIM_ATTAQUE) {
            j->frameActuel.y = 2 * HAUTEUR_FRAME;
        } else if (j->animation == ANIM_MORT) {
            j->frameActuel.y = 3 * HAUTEUR_FRAME; // Ligne pour mort
        } else if (j->animation == ANIM_GAGNER) {
            j->frameActuel.y = 4 * HAUTEUR_FRAME; // Ligne pour victoire
        } else {
            j->frameActuel.y = 0 * HAUTEUR_FRAME;
        }

        j->derniereAnimation = maintenant;
    }
}

void changerAnimation(Joueur* j, TypeAnimation nouvelleAnim) {
    // Si l'animation est déjà celle que l'on veut, on ne fait rien
    if (j->animation != nouvelleAnim) {
        j->animation = nouvelleAnim;
        j->frameIndex = 0;
        j->frameActuel.x = 0;

        // Ajout de la gestion de la direction dans l'animation
        if (nouvelleAnim == ANIM_MARCHE) {
            if (j->direction == 1) {
                // Marche à gauche (peut-être ajouter une inversion de sprite ici si nécessaire)
            } else {
                // Marche à droite
            }
        }
    }
}

void handleEvent(Joueur* j, SDL_Event* event) {
    // Si le joueur est en animation de mort, on ne traite plus aucun événement
    if (j->animation == ANIM_MORT || j->animation == ANIM_GAGNER) {
        return; // On arrête toute gestion des événements si le joueur est mort
    }

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_LEFT:
                j->direction = 1;  // Déplacement à gauche
                changerAnimation(j, ANIM_MARCHE);
                break;
            case SDLK_RIGHT:
                j->direction = 0;  // Déplacement à droite
                changerAnimation(j, ANIM_MARCHE);
                break;
            case SDLK_UP:
                if (j->auSol) {
                    j->positionEcran.y -= 150;  // Sauter
                    changerAnimation(j, ANIM_SAUT);
                    j->auSol = false;
                    j->enSaut = true;
                }
                break;
            case SDLK_SPACE:
                changerAnimation(j, ANIM_ATTAQUE);  // Attaque
                break;
        }
    } else if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_RIGHT) {
            changerAnimation(j, ANIM_IDLE);  // Retour à l'état inactif
            j->direction = -1;  // Arrêt du mouvement
        }
    }
}

void reduireVies(Joueur* j, int montant) {
    j->vies -= montant;
    if (j->vies <= 0) {
        j->vies = 0;
        if (j->animation != ANIM_MORT) {  // Si l'animation n'est pas déjà en cours
            changerAnimation(j, ANIM_MORT);  // Démarre l'animation de mort
        }
        j->estActif = false;  // Le joueur est inactif pendant l'animation de mort
    }
}


void dessinerJoueur(SDL_Surface* ecran, Joueur* j) {
    SDL_BlitSurface(j->spriteSheet, &j->frameActuel, ecran, &j->positionEcran);
}

void libererJoueur(Joueur* j) {
    if (j->spriteSheet) {
        SDL_FreeSurface(j->spriteSheet);
    }
}

void initCoeurs(Joueur* j) {
    for (int i = 0; i < 3; i++) {
        j->coeurs[i] = IMG_Load("coeur.png");
        if (!j->coeurs[i]) {
            fprintf(stderr, "Erreur chargement image coeur %d: %s\n", i, IMG_GetError());
        }
    }
}

void afficherVies(SDL_Surface* ecran, Joueur* j, int xDepart) {
    SDL_Rect pos = {xDepart, 30, 0, 0};
    for (int i = 0; i < 3; i++) {
        if (i < j->vies) {
            SDL_BlitSurface(j->coeurs[i], NULL, ecran, &pos);
        }
        pos.x += j->coeurs[i]->w + 5;
    }
}

void gererScore(SDL_Surface* ecran, int score, int xDepart) {
    char texteScore[50];
    sprintf(texteScore, "Score: %d", score);
    TTF_Font* font = TTF_OpenFont("Arial.TTF", 24);
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return;
    }
    SDL_Color couleur = {255, 255, 255};
    SDL_Surface* surfaceScore = TTF_RenderText_Solid(font, texteScore, couleur);
    if (surfaceScore) {
        SDL_Rect positionScore = {xDepart, 10, 0, 0}; // Score en haut à gauche
        SDL_BlitSurface(surfaceScore, NULL, ecran, &positionScore);
        SDL_FreeSurface(surfaceScore);
    }
    TTF_CloseFont(font);
}
void handleEventJoueur2(Joueur* j, SDL_Event* event) {
    // Si le joueur est en animation de mort, on ne traite plus aucun événement
    if (j->animation == ANIM_MORT || j->animation == ANIM_GAGNER) {
        return; // On arrête toute gestion des événements si le joueur est mort
    }

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_q:  // Déplacement à gauche pour joueur 2
                j->direction = 1;
                changerAnimation(j, ANIM_MARCHE);
                break;
            case SDLK_d:  // Déplacement à droite pour joueur 2
                j->direction = 0;
                changerAnimation(j, ANIM_MARCHE);
                break;
            case SDLK_z:  // Sauter pour joueur 2
                if (j->auSol) {
                    j->positionEcran.y -= 150;  // Sauter
                    changerAnimation(j, ANIM_SAUT);
                    j->auSol = false;
                    j->enSaut = true;
                }
                break;
            case SDLK_s:  // Attaque pour joueur 2
                changerAnimation(j, ANIM_ATTAQUE);
                break;
        }
    } else if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_q || event->key.keysym.sym == SDLK_d) {
            changerAnimation(j, ANIM_IDLE);  // Retour à l'état inactif
            j->direction = -1;  // Arrêt du mouvement
        }
    }
}




