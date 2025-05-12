#include "menu.h"
#include <SDL/SDL_ttf.h>


void afficher(score *s, SDL_Surface *ecran, int mode, int *running) {
    SDL_BlitSurface(s->back, NULL, ecran, NULL);  // Affiche l’arrière-plan

    // Affiche le bouton "Valider"
    SDL_BlitSurface(s->valider_btt[0], NULL, ecran, &s->pos_valider);

    // -------- Affichage du label "Saisir nom/Pseudo:" --------
    TTF_Font *font_label = TTF_OpenFont("arial.ttf", 32);  // Police du label
    SDL_Color textColor = {0, 0, 0};  // Couleur du texte (noir)
    if (font_label) {
        SDL_Surface *label = TTF_RenderText_Solid(font_label, "Saisir votre nom :", textColor);
        SDL_Rect pos_label = {600, 300};  // Position du label
        SDL_BlitSurface(label, NULL, ecran, &pos_label);  // Afficher le label
        SDL_FreeSurface(label);  // Libérer la surface du label
        TTF_CloseFont(font_label);  // Fermer la police du label
    } else {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
    }

    // -------- Rectangle de saisie du pseudo --------
    SDL_Rect input_box = {500, 380, 500, 70};  // Rectangle de saisie du pseudo
    SDL_Rect border = {input_box.x - 2, input_box.y - 2, input_box.w + 4, input_box.h + 4};  // Bordure autour de la zone de texte
    SDL_FillRect(ecran, &border, SDL_MapRGB(ecran->format, 0, 0, 255));  // Remplir le bord avec une couleur bleue
    SDL_FillRect(ecran, &input_box, SDL_MapRGB(ecran->format, 255, 255, 255)); // Remplir la zone de saisie avec du blanc

    // -------- Affichage du pseudo saisi --------
    SDL_Surface *pseudoSurface = TTF_RenderText_Solid(s->font, s->pseudo, textColor);
    SDL_Rect pseudoPos = {input_box.x + 10, input_box.y + 10};  // Position du texte
    if (pseudoSurface) {
        SDL_BlitSurface(pseudoSurface, NULL, ecran, &pseudoPos);  // Afficher le pseudo saisi
        SDL_FreeSurface(pseudoSurface);  // Libérer la surface du pseudo
    } else {
        printf("Erreur d'affichage du texte pseudo : %s\n", TTF_GetError());
    }

    SDL_Flip(ecran);
}





// Fonction pour initialiser les éléments du menu (bouton, police, etc.)
void init_score(score *s) {
    s->back = IMG_Load("background.jpg");
    s->valider_btt[0] = IMG_Load("validernormal.png");
    s->valider_btt[1] = IMG_Load("validerappuye.png");
    s->pos_valider.x = 620;
    s->pos_valider.y = 550;

    s->font = TTF_OpenFont("arial.ttf", 32);
    s->textColor.r = 0;  // Composant rouge
    s->textColor.g = 0;  // Composant vert
    s->textColor.b = 0;  // Composant bleu

    s->pseudo[0] = '\0';  // Initialiser la chaîne du pseudo
    s->score = 0;
    s->parties_jouees = 0;
}

// Fonction pour gérer les événements clavier/souris pour la saisie de pseudo et le clic sur "Valider"
void gerer_evenements(score *s, SDL_Surface *ecran, int *mode, int *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = 0;
                break;

            case SDL_KEYDOWN:
                if (*mode == 1) {  // Saisie du pseudo
                    size_t len = strlen(s->pseudo);

                    if (event.key.keysym.sym == SDLK_BACKSPACE && len > 0) {
                        s->pseudo[len - 1] = '\0';
                    } else if (event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= SDLK_z && len < 20) {
                        s->pseudo[len] = (char)event.key.keysym.sym;
                        s->pseudo[len + 1] = '\0';
                    }

                    // Quand le joueur appuie sur Entrée
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        // Changer le mode pour afficher le score
                        *mode = 2;  // Mode affichage du score
                    }

                    // Si la touche Échap est pressée, quitter
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        printf("Touche Échap pressée, quitter...\n");
                        *running = 0;
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x;
                    int y = event.button.y;

                    // Gestion du clic sur le bouton "Valider"
                    if (*mode == 1 && x >= s->pos_valider.x && x <= s->pos_valider.x + s->valider_btt[0]->w &&
                        y >= s->pos_valider.y && y <= s->pos_valider.y + s->valider_btt[0]->h) {
                        *mode = 2;  // Passe en mode affichage du score
                    }
                }
                break;
        }
    }
}

// Fonction pour afficher le menu avec pseudo et bouton (pas de modification majeure ici)
void afficher_score(SDL_Surface *screen, const char *pseudo, int score, TTF_Font *font) {
    SDL_Color white = {255, 255, 255};
    char scoreText[100];
    sprintf(scoreText, "Votre score : %d", score);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, white);
    SDL_Rect textPosition = {100, 100};
    SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
    SDL_FreeSurface(textSurface);

    SDL_Flip(screen);
    SDL_Delay(3000);  // Attendre 3 secondes pour afficher le score
}

// Fonction pour ajouter un score au tableau des meilleurs scores (trié)
void ajouter_score(MeilleurScore *top, int *nb_scores, const char *pseudo, int score) {
    if (*nb_scores < 3) {
        strcpy(top[*nb_scores].pseudo, pseudo);
        top[*nb_scores].score = score;
        (*nb_scores)++;
    } else {
        // Trouve le score à remplacer si nécessaire
        for (int i = 0; i < 3; i++) {
            if (score > top[i].score) {
                for (int j = 2; j > i; j--) {
                    top[j] = top[j - 1];
                }
                strcpy(top[i].pseudo, pseudo);
                top[i].score = score;
                break;
            }
        }
    }
}
void afficher_resultat(SDL_Surface *screen, SDL_Surface *result_bg, TTF_Font *font, const char *pseudo, int score) {
SDL_Color color = {0, 0, 0};
SDL_BlitSurface(result_bg, NULL, screen, NULL);
char texte[100];
sprintf(texte, "Votre score : %d", score);

SDL_Surface *textSurface = TTF_RenderText_Solid(font, texte, color);
SDL_Rect textPos = {350, 400};
SDL_BlitSurface(textSurface, NULL, screen, &textPos);
SDL_FreeSurface(textSurface);

SDL_Surface *pseudoSurface = TTF_RenderText_Solid(font, pseudo, color);
SDL_Rect pseudoPos = {350, 300};
SDL_BlitSurface(pseudoSurface, NULL, screen, &pseudoPos);
SDL_FreeSurface(pseudoSurface);

SDL_Flip(screen);


} 




void afficher_meilleurs_scores_fenetre(SDL_Surface *screen, MeilleurScore top[], int nb_scores, SDL_Surface *etoiles[], TTF_Font *font) {
    SDL_Surface *background = IMG_Load("score3.png");
    if (!background) {
        printf("Erreur chargement image score3.png : %s\n", IMG_GetError());
        return;
    }

    SDL_Color white = {0, 0, 0};
    SDL_Event event;
    int attendre = 1;

    while (attendre) {
        SDL_BlitSurface(background, NULL, screen, NULL);

        for (int i = 0; i < nb_scores; i++) {
            char texte[128];
            snprintf(texte, sizeof(texte), " %s : %d",  top[i].pseudo, top[i].score);
            SDL_Surface *msg = TTF_RenderText_Solid(font, texte, white);
            if (msg) {
                // Position étoile
                SDL_Rect pos_etoile = {400, 247 + i * 100};
                if (etoiles[i]) {
                    SDL_BlitSurface(etoiles[i], NULL, screen, &pos_etoile);
                }

                // Position texte à droite de l’étoile
                SDL_Rect pos_texte = {450, 260 + i * 100};
                SDL_BlitSurface(msg, NULL, screen, &pos_texte);
                SDL_FreeSurface(msg);
            } else {
                printf("Erreur rendu texte : %s\n", TTF_GetError());
            }
        }

        

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ||
                event.type == SDL_MOUSEBUTTONDOWN) {
                attendre = 0;
            }
        }

        SDL_Delay(100);
    }

    SDL_FreeSurface(background);
}





