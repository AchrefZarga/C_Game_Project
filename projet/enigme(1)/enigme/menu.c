#include "menu_enigme.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

int init(SDL_Surface **screen, TTF_Font **font) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 0;
    if (TTF_Init() < 0) return 0;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 0;

    *screen = SDL_SetVideoMode(1440, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!*screen) return 0;

    *font = TTF_OpenFont("arial.ttf", 28);
    if (!*font) return 0;

    return 1;
}

int load_questions(const char *filename, Quiz *quiz) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    
    quiz->total = 0;
    quiz->current = 0;
    quiz->score = 0;
    quiz->livesGained = 0;

    while (fgets(quiz->questions[quiz->total].question, MAX_TEXT, f)) {
        fgets(quiz->questions[quiz->total].A, MAX_TEXT, f);
        fgets(quiz->questions[quiz->total].B, MAX_TEXT, f);
        fgets(quiz->questions[quiz->total].C, MAX_TEXT, f);
        char correct[4];
        fgets(correct, 4, f);
        quiz->questions[quiz->total].correct = correct[0];
        quiz->total++;
        if (quiz->total >= MAX_QUESTIONS) break;
    }

    fclose(f);
    return 1;
}

void render_main_menu(SDL_Surface *screen, Button btnQuiz, Button btnPuzzle) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_Surface *quiz = is_hovered(btnQuiz, x, y) ? btnQuiz.hover : btnQuiz.normal;
    SDL_Surface *puzzle = is_hovered(btnPuzzle, x, y) ? btnPuzzle.hover : btnPuzzle.normal;

    SDL_BlitSurface(quiz, NULL, screen, &btnQuiz.pos);
    SDL_BlitSurface(puzzle, NULL, screen, &btnPuzzle.pos);
    SDL_Flip(screen);
}

void render_quiz(SDL_Surface *screen, TTF_Font *font, Quiz *quiz, Button btnA, Button btnB, Button btnC) {
    SDL_Surface *bg = IMG_Load("background1.png");
    if (bg) SDL_BlitSurface(bg, NULL, screen, NULL);

    SDL_Color black = {0, 0, 0};
    SDL_Surface *text;
    SDL_Rect pos = {50, 50};
    Question *q = &quiz->questions[quiz->current];

    text = TTF_RenderText_Blended(font, q->question, black);
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);

    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_Surface *a_img = is_hovered(btnA, x, y) ? btnA.hover : btnA.normal;
    SDL_Surface *b_img = is_hovered(btnB, x, y) ? btnB.hover : btnB.normal;
    SDL_Surface *c_img = is_hovered(btnC, x, y) ? btnC.hover : btnC.normal;

    SDL_BlitSurface(a_img, NULL, screen, &btnA.pos);
    SDL_BlitSurface(b_img, NULL, screen, &btnB.pos);
    SDL_BlitSurface(c_img, NULL, screen, &btnC.pos);

    pos.x = 150;
    pos.y = 250;
    text = TTF_RenderText_Blended(font, q->A, black);
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);

    pos.y = 350;
    text = TTF_RenderText_Blended(font, q->B, black);
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);

    pos.y = 450;
    text = TTF_RenderText_Blended(font, q->C, black);
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);

    SDL_Flip(screen);

    if (bg) SDL_FreeSurface(bg);
}
void render_vies(SDL_Surface *screen, SDL_Surface *coeur, int vies) {
    for (int i = 0; i < vies; i++) {
        SDL_Rect dst;
        dst.x = screen->w - 20 * (i + 1);
        dst.y = 10;
        dst.w = 16;
        dst.h = 16;

        SDL_Surface *small = SDL_CreateRGBSurface(0, dst.w, dst.h, coeur->format->BitsPerPixel,
                                                  screen->format->Rmask, screen->format->Gmask,
                                                  screen->format->Bmask, screen->format->Amask);

        SDL_BlitSurface(coeur, NULL, small, NULL);
        SDL_BlitSurface(small, NULL, screen, &dst);
        SDL_FreeSurface(small);
    }
}
char get_answer_clicked(Button a, Button b, Button c, int x, int y) {
    if (is_hovered(a, x, y)) return 'A';
    if (is_hovered(b, x, y)) return 'B';
    if (is_hovered(c, x, y)) return 'C';
    return '\0';
}
void remove_question_mark(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '?') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}
