#include "mini_map.h"
#include <SDL/SDL_image.h>

SDL_Surface *background = NULL;
SDL_Surface *minimap = NULL;
SDL_Surface *backgroundMask = NULL;

void chargerArrierePlans() {
    background = load_image("background1.jpg");
    minimap = load_image("minni.png");
    backgroundMask = load_image("backmask.png");
}

SDL_Surface* load_image(const char *filename) {
    SDL_Surface *loadedImage = IMG_Load(filename);
    if (!loadedImage) {
        printf("Erreur chargement image %s: %s\n", filename, IMG_GetError());
        return NULL;
    }

    SDL_Surface *optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}

void animer_joueur(Player *p) {
    Uint32 now = SDL_GetTicks();
    if (now > p->lastUpdate + p->frameDelay) {
        p->lastUpdate = now;

  
        p->taille += p->direction;
        if (p->taille >= 30 || p->taille <= 10)
            p->direction *= -1;

        
        p->colorPhase = (p->colorPhase + 1) % 6;
        switch (p->colorPhase) {
            case 0: p->color = (SDL_Color){255, 0, 0}; break;
            case 1: p->color = (SDL_Color){255, 127, 0}; break;
            case 2: p->color = (SDL_Color){255, 255, 0}; break;
            case 3: p->color = (SDL_Color){0, 255, 0}; break;
            case 4: p->color = (SDL_Color){0, 0, 255}; break;
            case 5: p->color = (SDL_Color){139, 0, 255}; break;
        }
    }
}

void draw_player(SDL_Surface *screen, Player *p) {
    SDL_Rect rect = {p->x - p->taille/2, p->y - p->taille/2, p->taille, p->taille};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, p->color.r, p->color.g, p->color.b));
}

void draw_minimap(SDL_Surface *screen, SDL_Surface *minimap, int player_x, int player_y, SDL_Rect camera) {
    SDL_Rect minimap_rect = {30, 0, minimap->w, minimap->h};

    // تحريك الميني-ماب بناءً على إحداثيات الكاميرا
    SDL_BlitSurface(minimap, &camera, screen, &minimap_rect); // موازاة الميني-ماب بالكاميرا

    // حساب موقع اللاعب داخل الميني-ماب بناءً على إحداثياته في اللعبة
    int mini_x = (player_x - camera.x) * minimap->w / background->w;
    int mini_y = (player_y - camera.y) * minimap->h / background->h;

    SDL_Rect player_rect = {mini_x, mini_y, 5, 5};
    SDL_FillRect(screen, &player_rect, SDL_MapRGB(screen->format, 255, 0, 0));
}


Uint32 GetPixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1: return *p;
        case 2: return *(Uint16 *)p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4: return *(Uint32 *)p;
        default: return 0;
    }
}

int CollisionParfaite(SDL_Surface *mask, int x, int y, int w, int h) {
    Uint32 pixelColor;
    Uint8 r, g, b;
    int px[8] = { x, x + w/2, x + w, x, x, x + w/2, x + w, x + w };
    int py[8] = { y, y, y, y + h/2, y + h, y + h, y + h, y + h/2 };

    for (int i = 0; i < 8; i++) {
        if (px[i] < 0 || py[i] < 0 || px[i] >= mask->w || py[i] >= mask->h) continue;

        pixelColor = GetPixel(mask, px[i], py[i]);
        SDL_GetRGB(pixelColor, mask->format, &r, &g, &b);

        if (r <= 60 && g <= 60 && b <= 60) {
            return 1;
        }
    }

    return 0;
}

int collision_AABB(SDL_Rect a, SDL_Rect b) {
    return !(a.x + a.w < b.x || a.x > b.x + b.w || a.y + a.h < b.y || a.y > b.y + b.h);
}

