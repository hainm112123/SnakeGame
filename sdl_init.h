#ifndef SDL_INIT_H_INCLUDED
#define SDL_INIT_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "Snake Game";

void logSDLError(ostream &os, const string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window *window, SDL_Renderer *renderer);

void waitUntilKeyPressed();

#endif // SDL_INIT_H_INCLUDED
