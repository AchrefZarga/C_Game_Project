#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

int initialize_game(SDL_Surface** screen, SDL_Surface** backgroundImage, SDL_Surface** puzzleImage, SDL_Surface** quizImage, 
                   SDL_Surface** optionA, SDL_Surface** optionB, SDL_Surface** optionC, Mix_Music** backgroundMusic, 
                   Mix_Music** drumMusic, TTF_Font** font, SDL_Surface** textSurface);

void display_main_screen(SDL_Event* event, int* quit, int* showText, Mix_Music* backgroundMusic, Mix_Music* drumMusic,
                         SDL_Rect* puzzleRect, SDL_Rect* quizRect, SDL_Surface* puzzleImage, SDL_Surface* quizImage,
                         SDL_Surface* backgroundImage, SDL_Surface* screenSurface, SDL_Rect* backgroundRect, 
                         int* hideOptions, SDL_Surface* optionA, SDL_Surface* optionB, SDL_Surface* optionC, 
                         SDL_Rect* optionARect, SDL_Rect* optionBRect, SDL_Rect* optionCRect,
                         int* optionAClicked, int* optionBClicked, int* optionCClicked,
                         SDL_Surface* optionA_clicked, SDL_Surface* optionB_clicked, SDL_Surface* optionC_clicked);

void display_question_screen(SDL_Surface* screenSurface, SDL_Surface* backgroundImage, SDL_Surface* puzzleImage, 
                             SDL_Surface* quizImage, SDL_Rect* backgroundRect, SDL_Rect* puzzleRect, SDL_Rect* quizRect, 
                             SDL_Rect* secondQuizRect, TTF_Font* font, int showText, int* hideOptions, 
                             SDL_Surface* optionA, SDL_Surface* optionB, SDL_Surface* optionC, SDL_Rect* optionARect, 
                             SDL_Rect* optionBRect, SDL_Rect* optionCRect, SDL_Rect* textRect, SDL_Surface* questionText, 
                             SDL_Color textColor, const char* questionMessage, SDL_Rect* answerTextRect, 
                             SDL_Surface* answerText, SDL_Color answerTextColor, const char* answerMessage,
                             int optionAClicked, int optionBClicked, int optionCClicked,
                             SDL_Surface* optionA_clicked, SDL_Surface* optionB_clicked, SDL_Surface* optionC_clicked);

void cleanup(SDL_Surface* backgroundImage, SDL_Surface* puzzleImage, SDL_Surface* quizImage, Mix_Music* backgroundMusic, 
             SDL_Surface* optionA, SDL_Surface* optionB, SDL_Surface* optionC, SDL_Surface* textSurface);

#endif
