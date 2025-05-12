#include "enemy.h"

void initialiserEnnemie(Ennemie *e, int niveau, int index) {
    char filename[30];
    sprintf(filename, "lvl%d_spritesheet.png", niveau);
    e->spriteSheet = IMG_Load(filename);
    if (!e->spriteSheet) {
        printf("Erreur chargement sprite sheet: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 6; col++) {
            int idx = row * 6 + col;
            e->frameRects[idx].x = col * 283;
            e->frameRects[idx].y = row * 277;
            e->frameRects[idx].w = 283;
            e->frameRects[idx].h = 277;
        }
    }

    e->niveau = niveau;
    e->etat = 1;
    e->vitesse = 2.0;
    e->acceleration = 0.1;
    e->frameIndex = 0;
    e->vie = VIE_MAX;
    e->direction = 1;
    e->position.w = 220;
    e->position.h = 220;
    e->lastAnimTime = SDL_GetTicks();

    // Position selon la zone (glace ou lave)
    if (index == 0) { // Glace
        e->position.x = 4449;
        e->position.y = 400;
        e->posMinX = e->position.x - 100;
        e->posMaxX = e->position.x + 100;
    } else { // Lave
        e->position.x = 8030;
        e->position.y = 514;
        e->posMinX = e->position.x - 100;
        e->posMaxX = e->position.x + 100;
    }

    if (niveau == 2) {
        e->posMinY = 300;
        e->posMaxY = 530;
    } else {
        e->posMinY = e->position.y;
        e->posMaxY = e->position.y;
    }
}

void initialiserBonus(Bonus pommes[], SDL_Surface *imageBonus1, SDL_Surface *imageBonus2) {
    SDL_Rect positions[8] = {
        {905, 532, 50, 57},    // Bonus dans la zone glace
        {1319, 442, 50, 57},    // Bonus dans la zone glace
        {2188, 442, 50, 57},    // Bonus dans la zone glace
        {2776, 436, 50, 57},    // Bonus dans la zone glace
        {5974, 364, 50, 76},   // Bonus dans la zone lave
        {6673, 412, 50, 76},   // Bonus dans la zone lave
        {9469, 556, 50, 76},   // Bonus dans la zone lave
        {9757, 436, 50, 76},    // Bonus dans la zone lave
    };

    for (int i = 0; i < 8; i++) {
        pommes[i].position = positions[i];
        pommes[i].image = (i < 4) ? imageBonus1 : imageBonus2;
        pommes[i].actif = 1;
    }
}



void afficherBonus(Bonus pommes[], int nb, SDL_Surface *ecran) {
    for (int i = 0; i < nb; i++) {
        if (pommes[i].actif) {
            SDL_BlitSurface(pommes[i].image, NULL, ecran, &pommes[i].position);
        }
    }
}



SDL_Color GetPixel(SDL_Surface *surface, int x, int y) {
    SDL_Color color = {0, 0, 0, 0};
    if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) return color;
    Uint32 col = *((Uint32*)((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel));
    SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);

    return color;

}



TypeSurface VerifierTypeSurface(SDL_Surface *masque, SDL_Rect position) {
    SDL_Color pixel = GetPixel(masque, position.x + position.w / 2, position.y + position.h);

    if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0)
        return OBSTACLE;
    else if ((pixel.r == 33 && pixel.g == 175 && pixel.b == 75) ||
             (pixel.r == 34 && pixel.g == 176 && pixel.b == 76))
        return PIEGE;

    return SOL;
}




int CollisionParfaite(SDL_Surface *backgroundMasque, SDL_Rect perso) {
    int points[8][2] = {{perso.x, perso.y}, {perso.x + perso.w/2, perso.y},
                        {perso.x + perso.w, perso.y}, {perso.x, perso.y + perso.h/2},
                        {perso.x, perso.y + perso.h}, {perso.x + perso.w/2, perso.y + perso.h},
                        {perso.x + perso.w, perso.y + perso.h}, {perso.x + perso.w, perso.y + perso.h/2}};
    for (int i = 0; i < 8; i++) {
        SDL_Color pixel = GetPixel(backgroundMasque, points[i][0], points[i][1]);
        if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) return 1;
    }
    return 0;
}



int collisionTrigonometrie(SDL_Rect a, SDL_Rect b) {
    float x1 = a.x + a.w/2.0, y1 = a.y + a.h/2.0;
    float x2 = b.x + b.w/2.0, y2 = b.y + b.h/2.0;
    float r1 = (a.w < a.h) ? a.w/2.0 : a.h/2.0;
    float r2 = (b.w < b.h) ? b.w/2.0 : b.h/2.0;
    float dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx*dx + dy*dy) <= (r1 + r2);

}





void afficherEnnemie(Ennemie e, SDL_Surface *ecran) {
    
    if (e.position.x + e.position.w > 0 && 
        e.position.x < ecran->w &&
        e.position.y + e.position.h > 0 && 
        e.position.y < ecran->h) {
        
       
        if (e.frameIndex >= 0 && e.frameIndex < 18) {
            SDL_BlitSurface(e.spriteSheet, &e.frameRects[e.frameIndex], ecran, &e.position);
            afficherEtatEnnemie(e, ecran);
        }
    }
}

void afficherEtatEnnemie(Ennemie e, SDL_Surface *ecran) {
    
    SDL_Rect contour = { e.position.x, e.position.y - 10, e.position.w, 5 };
    SDL_FillRect(ecran, &contour, SDL_MapRGB(ecran->format, 0, 0, 0));

   
    SDL_Rect barreVie = { e.position.x, e.position.y - 10, e.vie * e.position.w / VIE_MAX, 5 };
    SDL_FillRect(ecran, &barreVie, SDL_MapRGB(ecran->format, 255, 0, 0));
}



void gererEtatEnnemie(Ennemie *e, int nouvelEtat) {
    if (e->etat == 0) return;

    if (e->etat != nouvelEtat) {
        e->etat = nouvelEtat;

        if (nouvelEtat == 2) {
            e->frameIndex = 6;
        } else if (nouvelEtat == 0) {
            e->frameIndex = 12;
        } else {
            e->frameIndex = 0;
        }
    }
}

void animerEnnemie(Ennemie *e) {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 delay = (e->etat == 0) ? 300 : 100; // Mort = 300 ms, sinon = 100 ms

    if (currentTime - e->lastAnimTime < delay) return;
    e->lastAnimTime = currentTime;

    int base = 0;
    if (e->etat == 2) base = 6;
    else if (e->etat == 0) base = 12;

    if (e->frameIndex < base || e->frameIndex >= base + FRAME_COUNT) {
        e->frameIndex = base;
    } else {
        e->frameIndex++;
        if (e->etat == 0 && e->frameIndex > 17) {
            e->frameIndex = 17; 
        } else if (e->frameIndex >= base + FRAME_COUNT) {
            e->frameIndex = base;
        }
    }

    printf("🎞️  Etat: %d, Frame: %d\n", e->etat, e->frameIndex);
}


void initialiserProjectile(Projectile *p, int niveau) {
    if (niveau == 1) {
        p->image = IMG_Load("snowball.png");
    } else {
        p->image = IMG_Load("fireball.png");
    }
    if (!p->image) {
        printf("Erreur chargement projectile: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    p->position.w = p->image->w;
    p->position.h = p->image->h;
    p->position.x = 0;
    p->position.y = 0;
    p->actif = 0;
    p->vitesse = 5;
    p->direction = 0;
}

void deplacerEnnemie(Ennemie *e, SDL_Rect joueurPos, SDL_Surface *backgroundMasque, Bonus pommes[], int nbPommes) {
    if (e->etat == 0) return;

    int dx = joueurPos.x - e->position.x;
    int dy = joueurPos.y - e->position.y;

    if (abs(dx) < DETECTION_RANGE && abs(dy) < DETECTION_RANGE &&
    joueurPos.x >= e->posMinX && joueurPos.x <= e->posMaxX) {
        gererEtatEnnemie(e, 2);
        if (dx > 0) {
            e->position.x += e->vitesse;
            e->direction = 0;
        } else {
            e->position.x -= e->vitesse;
            e->direction = 1;
        }
        if (e->niveau == 2) {
            if (dy > 0) e->position.y += e->vitesse;
            else e->position.y -= e->vitesse;
        }
    } else {
        gererEtatEnnemie(e, 1);
        if (e->direction == 0) e->position.x += e->vitesse;
        else e->position.x -= e->vitesse;

        if (e->position.x >= e->posMaxX) e->direction = 1;
        if (e->position.x <= e->posMinX) e->direction = 0;

        if (e->niveau == 2) {
            if (rand() % 2) e->position.y += e->vitesse;
            else e->position.y -= e->vitesse;

            if (e->position.y > e->posMaxY) e->position.y = e->posMaxY;
            if (e->position.y < e->posMinY) e->position.y = e->posMinY;
        }
    }

    
    TypeSurface surface = VerifierTypeSurface(backgroundMasque, e->position);
    if (surface == PIEGE) {
        e->vie -= 20;
        if (e->vie <= 0) gererEtatEnnemie(e, 0);
        if (e->direction == 0) e->direction = 1;
        else e->direction = 0;
    }

    if (e->niveau == 2 && surface == OBSTACLE) {
    
    e->position.y -= e->vitesse + 30;

    
    if (joueurPos.x > e->position.x) {
        e->direction = 0; 
    } else {
        e->direction = 1; 
    }
}


    
 
}
void gererProjectiles(Projectile *p, SDL_Surface *ecran, SDL_Surface *backgroundMasque, SDL_Rect joueurPos) {
    if (p->actif) {
        if (p->direction == 0) {
            p->position.x += p->vitesse;
        } else {
            p->position.x -= p->vitesse;
        }

        SDL_BlitSurface(p->image, NULL, ecran, &p->position);

        
        if (collisionTrigonometrie(p->position, joueurPos)) {
            p->actif = 0;  
        }

        
        if (CollisionParfaite(backgroundMasque, p->position) ||
            p->position.x < 0 || p->position.x > ecran->w) {
            p->actif = 0;
        }
    }
}

void gererAttaqueEnnemie(Ennemie *e, SDL_Rect joueurPos, Projectile *p) {
    if (e->etat == 2) {
        // Tirer uniquement à la frame précise
        if (e->frameIndex == 11 && !p->actif) {
            p->actif = 1;
            p->direction = e->direction;

            if (e->direction == 0) {
                p->position.x = e->position.x + e->position.w;
            } else {
                p->position.x = e->position.x - p->image->w;
            }

            p->position.y = e->position.y + e->position.h / 2 - p->image->h / 2;
        }
    }
}







