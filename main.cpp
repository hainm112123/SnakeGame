#include <bits/stdc++.h>
#include <SDL.h>

#include "sdl_init.h"
#include "PlayGround.h"
#include "Snake.h"
#include "Painter.h"
#include "gallery.h"

#define CLOCK_NOW chrono::system_clock::now

using namespace std;

typedef chrono::duration<double> ElapsedTime;

const double STEP_DELAY = 0.2;
const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 30;

Gallery *gallery;

void renderSplashScreen() {
    waitUntilKeyPressed();
}

void drawCherry(Painter &painter, int left, int top) {
    SDL_Rect dst = {left + 5, top + 5, CELL_SIZE - 10, CELL_SIZE - 10};
    painter.createImage(gallery->getImage(PIC_CHERRY), NULL, &dst);
}

void drawSnake(Painter &painter, int left, int top, vector<Position> pos, Direction dir) {
    vector<int> dx = {1, 1, -1, -1};
    vector<int> dy = {-1, 1, -1, 1};
    vector<PictureID> IDs = {PIC_BODY_BOTTOM_LEFT, PIC_BODY_BOTTOM_RIGHT, PIC_BODY_TOP_LEFT, PIC_BODY_TOP_RIGHT};

    for (int i = 0; i < int(pos.size()); ++ i) {
        SDL_Rect dst = {left + pos[i].y * CELL_SIZE + 1, top + pos[i].x * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2};
        SDL_Texture *texture = NULL;

        if (i == int(pos.size()) - 1) {
            switch(dir) {
                case UP:
                    texture = gallery->getImage(PIC_HEAD_UP);
                    break;
                case DOWN:
                    texture = gallery->getImage(PIC_HEAD_DOWN);
                    break;
                case LEFT:
                    texture = gallery->getImage(PIC_HEAD_LEFT);
                    break;
                case RIGHT:
                    texture = gallery->getImage(PIC_HEAD_RIGHT);
                    break;
            }
        }
        else if (i == 0) {
            if (pos[i + 1].x == pos[i].x) {
                texture = gallery->getImage(pos[i + 1].y > pos[i].y ? PIC_TAIL_LEFT : PIC_TAIL_RIGHT);
            }
            else {
                texture = gallery->getImage(pos[i + 1].x > pos[i].x ? PIC_TAIL_UP : PIC_TAIL_DOWN);
            }
        }
        else {
            if (pos[i - 1].x == pos[i].x && pos[i].x == pos[i + 1].x) {
                texture = gallery->getImage(PIC_BODY_HORIZONTAL);
            }
            if (pos[i - 1].y == pos[i].y && pos[i].y == pos[i + 1].y) {
                texture = gallery->getImage(PIC_BODY_VERTICAL);
            }
            for (int j = 0; j < 4; ++ j) {
                if ((pos[i - 1].y == pos[i].y + dy[j] && pos[i + 1].x == pos[i].x + dx[j]) || (pos[i + 1].y == pos[i].y + dy[j] && pos[i - 1].x == pos[i].x + dx[j])) {
                    texture = gallery->getImage(IDs[j]);
                }
            }
        }
        painter.createImage(texture, NULL, &dst);
    }
}

void renderGamePlay(SDL_Renderer *renderer, const PlayGround &playGround, Painter &painter) {
    int top = 0, left = 0;
    int width = playGround.getWidth(), height = playGround.getHeight();
    painter.clearWithBgColor(GREEN_COLOR);
    painter.setColor(WHITE_COLOR);
    for (int i = 0; i <= width; ++ i) {
        painter.setAngle(-90);
        painter.setPosition(left + i * CELL_SIZE, top);
        painter.moveForward(height * CELL_SIZE);
    }
    for (int i = 0; i <= height; ++ i) {
        painter.setAngle(0);
        painter.setPosition(left, top + i * CELL_SIZE);
        painter.moveForward(width * CELL_SIZE);
    }

    Position cherry = playGround.getCherry();
    drawCherry(painter, left + cherry.y * CELL_SIZE, top + cherry.x * CELL_SIZE);
    vector<Position> snakePositions = playGround.getSnakePositions();
    drawSnake(painter, left, top, snakePositions, playGround.getSnakeDirection());

    SDL_RenderPresent(renderer);
}

UserInput interpretEvent(SDL_Event e) {
    if (e.type == SDL_KEYUP) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: return KEY_UP;
            case SDLK_DOWN: return KEY_DOWN;
            case SDLK_LEFT: return KEY_LEFT;
            case SDLK_RIGHT: return KEY_RIGHT;
        }
    }
    return NO_INPUT;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    SDL_Window *window;
    SDL_Renderer *renderer;
    initSDL(window, renderer);

    Painter painter(window, renderer);
    gallery = new Gallery(painter);

    renderSplashScreen();
    PlayGround playGround(BOARD_WIDTH, BOARD_HEIGHT);
    renderGamePlay(renderer, playGround, painter);
    SDL_Event e;
    auto start = CLOCK_NOW();
    while (playGround.isGameRunning()) {
        while (SDL_PollEvent(&e) != 0) {
            playGround.processUserInput(interpretEvent(e));
        }

        auto _end = CLOCK_NOW();
        ElapsedTime elapsed = _end - start;
        if (elapsed.count() > STEP_DELAY) {
            if (!playGround.nextStep()) {
                cout << "Game Over!\n";
                break;
            }
            renderGamePlay(renderer, playGround, painter);
            start = _end;
        }

        SDL_Delay(1);
    }

    waitUntilKeyPressed();
    delete gallery;
    quitSDL(window, renderer);

    return 0;
}
