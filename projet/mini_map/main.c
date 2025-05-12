#include "mini_map.h"
#include <SDL/SDL_image.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_EnableKeyRepeat(0, 0);

    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) return -1;

    chargerArrierePlans();
    if (!background || !minimap || !backgroundMask) return -1;

    Player joueur = {100, 100, 20, 1, {255, 0, 0, 0}, 0, 100, 0, 0};

    SDL_Rect camera = {0, 0, 800, 600};

    int running = 1;
    SDL_Event event;
    int move_up = 0, move_down = 0, move_left = 0, move_right = 0;
    int collisionBB_detected = 0;
    int collisionParfaite_detected = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: move_up = 1; break;
                    case SDLK_DOWN: move_down = 1; break;
                    case SDLK_LEFT: move_left = 1; break;
                    case SDLK_RIGHT: move_right = 1; break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: move_up = 0; break;
                    case SDLK_DOWN: move_down = 0; break;
                    case SDLK_LEFT: move_left = 0; break;
                    case SDLK_RIGHT: move_right = 0; break;
                    default: break;
                }
            }
        }

        int old_x = joueur.x;
        int old_y = joueur.y;

        if (move_up) joueur.y -= 1;
        if (move_down) joueur.y += 1;
        if (move_left) joueur.x -= 1;
        if (move_right) joueur.x += 1;

        if (CollisionParfaite(backgroundMask, joueur.x - PLAYER_RADIUS, joueur.y - PLAYER_RADIUS, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2)) {
            if (!collisionParfaite_detected) {
                printf("🎯 Collision parfaite !\n");
                collisionParfaite_detected = 1;
            }
            joueur.x = old_x;
            joueur.y = old_y;
        } else {
            collisionParfaite_detected = 0;
        }

        if (joueur.animating) animer_joueur(&joueur);

        // كاميرا رئيسية
        camera.x = joueur.x - camera.w / 2;
        camera.y = joueur.y - camera.h / 2;

        if (camera.x < 0) camera.x = 0;
        if (camera.y < 0) camera.y = 0;
        if (camera.x > background->w - camera.w) camera.x = background->w - camera.w;
        if (camera.y > background->h - camera.h) camera.y = background->h - camera.h;

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(background, &camera, screen, NULL);

        // رسم الميني-ماب مع الكاميرا
        draw_minimap(screen, minimap, joueur.x, joueur.y, camera);

        SDL_Rect playerOnScreen = {joueur.x - camera.x - joueur.taille/2, joueur.y - camera.y - joueur.taille/2, joueur.taille, joueur.taille};
        SDL_FillRect(screen, &playerOnScreen, SDL_MapRGB(screen->format, joueur.color.r, joueur.color.g, joueur.color.b));

        SDL_Flip(screen);
        SDL_Delay(10);
    }

    SDL_FreeSurface(background);
    SDL_FreeSurface(minimap);
    SDL_FreeSurface(backgroundMask);
    SDL_Quit();
    return 0;
}

