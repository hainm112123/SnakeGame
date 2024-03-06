#ifndef PLAYGROUND_H_INCLUDED
#define PLAYGROUND_H_INCLUDED

#include<bits/stdc++.h>
#include "Snake.h"

using namespace std;

enum CellType {
    CELL_EMPTY = 0,
    CELL_SNAKE,
    CELL_CHERRY
};

enum GameStatus {
    GAME_RUNNING = 1,
    GAME_STOP = 2,
    GAME_WON = 4 | GAME_STOP,
    GAME_LOST = 8 | GAME_STOP
};

class PlayGround {
    int width, height;
    vector<vector<CellType>> squares;
    Snake snake;
    int score;
    GameStatus status;
    Position cherry;

public:
    PlayGround(int width, int height);

    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
    vector<vector<CellType>> getSquares() const {
        return squares;
    }

    bool isGameRunning() const {
        return status == GAME_RUNNING;
    }
    void processUserInput(UserInput input);
    bool nextStep();
    void changeCellState(Position pos, CellType type);
    CellType getCellState(Position pos);
    void addCherry();
    Position getCherry() const {
        return cherry;
    }
    void setGameStatus(GameStatus newStatus);
    vector<Position> getSnakePositions() const;
    Direction getSnakeDirection() const {
        return snake.direction;
    }
};

#endif // PLAYGROUND_H_INCLUDED
