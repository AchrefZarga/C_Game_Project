#ifndef MENU_ENIGME_H
#define MENU_ENIGME_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#define MAX_QUESTIONS 10
#define MAX_TEXT 256

typedef struct {
    SDL_Surface *normal;
    SDL_Surface *hover;
    SDL_Rect pos;
} Button;

typedef struct {
    char question[MAX_TEXT];
    char A[MAX_TEXT];
    char B[MAX_TEXT];
    char C[MAX_TEXT];
    char correct;
} Question;

typedef struct {
    Question questions[MAX_QUESTIONS];
    int current;
    int total;
    int score;
    int livesGained;
} Quiz;

int init(SDL_Surface **screen, TTF_Font **font);
int load_questions(const char *filename, Quiz *quiz);

// ✅ Corrigé :
void render_vies(SDL_Surface *screen, SDL_Surface *coeur, int vies);
void render_main_menu(SDL_Surface *screen, Button quizBtn, Button puzzleBtn);
void render_quiz(SDL_Surface *screen, TTF_Font *font, Quiz *quiz, Button btnA, Button btnB, Button btnC);
char get_answer_clicked(Button a, Button b, Button c, int x, int y);
int is_hovered(Button b, int x, int y);

#endif
