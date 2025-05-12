#include "menu_enigme.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>

void render_timer_bar(SDL_Surface *screen, Uint32 startTime, Uint32 duration) {
    Uint32 elapsed = SDL_GetTicks() - startTime;
    float ratio = (elapsed >= duration) ? 0.0f : 1.0f - (float)elapsed / duration;

    int barWidth = 300;
    int barHeight = 20;
    int barX = (screen->w - barWidth) / 2;
    int barY = screen->h - 100;

    SDL_Rect barBg = {barX, barY, barWidth, barHeight};
    SDL_Rect barFg = barBg;
    barFg.w = (int)(barFg.w * ratio);

    Uint32 bgColor = SDL_MapRGB(screen->format, 100, 100, 100);
    Uint32 fgColor = SDL_MapRGB(screen->format, 255, 0, 0);

    SDL_FillRect(screen, &barBg, bgColor);
    SDL_FillRect(screen, &barFg, fgColor);
}

int is_hovered(Button b, int x, int y) {
    return x >= b.pos.x && x <= b.pos.x + b.normal->w &&
           y >= b.pos.y && y <= b.pos.y + b.normal->h;
}

void render_score(SDL_Surface *screen, TTF_Font *font, int score) {
    if (!font) return;

    SDL_Color black = {0, 0, 0};
    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);

    SDL_Surface *scoreSurface = TTF_RenderText_Blended(font, scoreText, black);
    if (!scoreSurface) {
        printf("Erreur TTF_RenderText_Blended (score) : %s\n", TTF_GetError());
        return;
    }

    SDL_Rect scorePos = {screen->w - scoreSurface->w - 200, screen->h / 2 + 10};
    SDL_BlitSurface(scoreSurface, NULL, screen, &scorePos);
    SDL_FreeSurface(scoreSurface);
}

void render_level(SDL_Surface *screen, TTF_Font *font, int level) {
    if (!font) return;

    SDL_Color blue = {0, 0, 255};
    char levelText[20];
    snprintf(levelText, sizeof(levelText), "Level: %d", level);

    SDL_Surface *levelSurface = TTF_RenderText_Blended(font, levelText, blue);
    if (!levelSurface) {
        printf("Erreur TTF_RenderText_Blended (level) : %s\n", TTF_GetError());
        return;
    }

    SDL_Rect levelPos = {screen->w - levelSurface->w - 200, screen->h / 2 - 40};
    SDL_BlitSurface(levelSurface, NULL, screen, &levelPos);
    SDL_FreeSurface(levelSurface);
}



int main() {
    SDL_Surface *screen = NULL, *bg = NULL;
    TTF_Font *font = NULL;

    if (!init(&screen, &font)) {
        printf("Erreur init\n");
        return 1;
    }

    bg = IMG_Load("background1.png");
    if (!bg) {
        printf("Erreur chargement background1.png: %s\n", IMG_GetError());
        return 1;
    }

    Button btnQuiz = {IMG_Load("QUIZ.png"), IMG_Load("quiz.png"), {200, 400}};
    Button btnPuzzle = {IMG_Load("puzzle.png"), IMG_Load("Puzzle.png"), {900, 400}};
    Button btnA = {IMG_Load("A.png"), IMG_Load("AA.png"), {50, 250}};
    Button btnB = {IMG_Load("B.png"), IMG_Load("BB.png"), {50, 350}};
    Button btnC = {IMG_Load("C.png"), IMG_Load("CC.png"), {50, 450}};
    Button btnQuit = {IMG_Load("QUITTER.png"), IMG_Load("QUITTER2.png"), {0, 0}};

    if (!btnQuiz.normal || !btnQuiz.hover || !btnPuzzle.normal || !btnPuzzle.hover ||
        !btnA.normal || !btnA.hover || !btnB.normal || !btnB.hover || !btnC.normal || !btnC.hover ||
        !btnQuit.normal || !btnQuit.hover) {
        printf("Erreur chargement image bouton : %s\n", IMG_GetError());
        return 1;
    }

    btnQuit.pos.x = screen->w - btnQuit.normal->w - 200;
    btnQuit.pos.y = screen->h - btnQuit.normal->h - 300;

    SDL_Surface *coeur = IMG_Load("heart.png");
    if (!coeur) {
        printf("Erreur chargement heart.png : %s\n", IMG_GetError());
        return 1;
    }

    Mix_Music *drumSound = Mix_LoadMUS("tombour.mp3");
    if (!drumSound) {
        printf("Erreur chargement tombour.mp3 : %s\n", Mix_GetError());
        return 1;
    }

    Quiz quiz;
    if (!load_questions("questions.txt", &quiz)) {
        printf("Erreur chargement questions\n");
        return 1;
    }

    bool running = true;
    int level = 1;
    int correctAnswersStreak = 0;
    Uint32 questionStartTime = 0;
    int vies = 5;
    const Uint32 questionDuration = 15000;

    Uint32 feedbackTime = 0;
    char feedbackResult = '\0';
    const Uint32 feedbackDuration = 1000;

    enum { MENU, QUIZ, PUZZLE } state = MENU;
    bool drumPlayed = false;
    SDL_Event e;

    while (running) {
        if (state == MENU || state == QUIZ)
            SDL_BlitSurface(bg, NULL, screen, NULL);

        if (state == MENU) {
            render_main_menu(screen, btnQuiz, btnPuzzle);
        } else if (state == QUIZ) {
            render_quiz(screen, font, &quiz, btnA, btnB, btnC);
            render_score(screen, font, quiz.score);
            render_level(screen, font, level);
            render_timer_bar(screen, questionStartTime, questionDuration);
            render_vies(screen, coeur, vies);

            int mx, my;
            SDL_GetMouseState(&mx, &my);
            SDL_Surface *quitImg = is_hovered(btnQuit, mx, my) ? btnQuit.hover : btnQuit.normal;
            SDL_BlitSurface(quitImg, NULL, screen, &btnQuit.pos);

            if (feedbackTime > 0) {
                if (SDL_GetTicks() - feedbackTime < feedbackDuration) {
                    SDL_Color color = (feedbackResult == 'G') ? (SDL_Color){0, 200, 0} : (SDL_Color){200, 0, 0};
                    const char *message = (feedbackResult == 'G') ? "Bonne reponse !" : "Mauvaise reponse !";
                    SDL_Surface *feedbackSurf = TTF_RenderText_Blended(font, message, color);
                    if (feedbackSurf) {
                        SDL_Rect msgPos = {screen->w / 2 - feedbackSurf->w / 2, 150};
                        SDL_BlitSurface(feedbackSurf, NULL, screen, &msgPos);
                        SDL_FreeSurface(feedbackSurf);
                    }
                } else {
                    feedbackTime = 0;
                    feedbackResult = '\0';
                    quiz.current++;
                    questionStartTime = SDL_GetTicks();

                    if (quiz.current >= quiz.total) {
                        if (quiz.score >= 7) quiz.livesGained++;
                        state = MENU;
                        drumPlayed = false;
                        quiz.current = 0;
                        quiz.score = 0;
                        vies = 5;
                    }
                }
            } else if (SDL_GetTicks() - questionStartTime > questionDuration) {
                feedbackResult = 'B';
                vies--;
                feedbackTime = SDL_GetTicks();

                if (vies <= 0) {
                    printf("Game Over !\n");
                    state = MENU;
                    drumPlayed = false;
                    quiz.current = 0;
                    quiz.score = 0;
                    vies = 5;
                }
            }
        } else if (state == PUZZLE) {
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int x = e.button.x, y = e.button.y;

                if (state == MENU) {
                    if (is_hovered(btnQuiz, x, y)) {
                        questionStartTime = SDL_GetTicks();
                        if (!drumPlayed) {
                            Mix_PlayMusic(drumSound, 1);
                            drumPlayed = true;
                        }
                        state = QUIZ;
                    } else if (is_hovered(btnPuzzle, x, y)) {
                        state = PUZZLE;
                    }
                } else if (state == QUIZ && feedbackTime == 0) {
                    if (is_hovered(btnQuit, x, y)) {
                        state = MENU;
                        drumPlayed = false;
                        quiz.current = 0;
                        quiz.score = 0;
                        vies = 5;
                        continue;
                    }

                    char clicked = get_answer_clicked(btnA, btnB, btnC, x, y);
                    if (clicked != '\0') {
                        if (clicked == quiz.questions[quiz.current].correct) {
                            quiz.score++;
                            correctAnswersStreak++;
                            if (correctAnswersStreak >= 3) {
                                level++;
                                correctAnswersStreak = 0;
                            }
                            feedbackResult = 'G';
                        } else {
                            correctAnswersStreak = 0;
                            vies--;
                            feedbackResult = 'B';
                            if (vies <= 0) {
                                printf("Game Over !\n");
                                state = MENU;
                                drumPlayed = false;
                                quiz.current = 0;
                                quiz.score = 0;
                                vies = 5;
                                continue;
                            }
                        }
                        feedbackTime = SDL_GetTicks();
                    }
                }
            }
        }

        SDL_Flip(screen);
    }

    Mix_FreeMusic(drumSound);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    SDL_FreeSurface(coeur);
    return 0;
}

