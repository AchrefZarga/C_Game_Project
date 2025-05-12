#include "enemy.h"

int main(int argc, char *argv[]) {
    SDL_Surface *ecran = NULL;
    SDL_Surface *background = NULL;
    SDL_Surface *backgroundMasque = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(5000, 700, 32, SDL_HWSURFACE);
    background = IMG_Load("background1.jpg");
    backgroundMasque = IMG_Load("Artboard 1back mask(1).png");

    if (!background || !backgroundMasque) {
        printf("Erreur chargement background : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

   
   SDL_Rect joueurPos = {500, 300, 32, 32}; // position factice pour tests
 
    
    Bonus pommes[8];

// Charger une seule fois les 2 images
SDL_Surface *imageBonus1 = IMG_Load("pomme_bonus1.png");
SDL_Surface *imageBonus2 = IMG_Load("pomme_bonus2.png");
if (!imageBonus1 || !imageBonus2) {
    printf("Erreur chargement bonus : %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
}

// Initialiser les 4 pommes avec les bonnes images
initialiserBonus(pommes, imageBonus1, imageBonus2);

   

    // Déclarations des entités
    
    Ennemie ennemis[2];
    Projectile projectiles[2];

    // Initialisation des bonus, ennemis et projectiles
   
    initialiserEnnemie(&ennemis[0], 1, 0); // niveau 1, index 0
    initialiserEnnemie(&ennemis[1], 2, 1); // niveau 2, index 1

    initialiserProjectile(&projectiles[0], 1);
    initialiserProjectile(&projectiles[1], 2);

    // Boucle principale
    int running = 1;
    SDL_Event event;

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Mise à jour des ennemis
        for (int i = 0; i < 2; i++) {
            if (ennemis[i].vie > 0) {
               deplacerEnnemie(&ennemis[i], joueurPos, backgroundMasque, pommes, 4);
                gererAttaqueEnnemie(&ennemis[i], joueurPos, &projectiles[i]);
                animerEnnemie(&ennemis[i]);
            }
        }

        // Affichage
        SDL_BlitSurface(background, NULL, ecran, NULL);

        for (int i = 0; i < 2; i++) {
            afficherEnnemie(ennemis[i], ecran);
            gererProjectiles(&projectiles[i], ecran, backgroundMasque, joueurPos);
        }
        afficherBonus(pommes, 8, ecran);

        

        SDL_Flip(ecran);
        SDL_Delay(16);
    }

    // Libération mémoire
    for (int i = 0; i < 2; i++) {
        SDL_FreeSurface(projectiles[i].image);
        SDL_FreeSurface(ennemis[i].spriteSheet);
    }
    SDL_FreeSurface(imageBonus1);
SDL_FreeSurface(imageBonus2);

    
    SDL_FreeSurface(background);
    SDL_FreeSurface(backgroundMasque);
    SDL_Quit();

    return 0;
}



