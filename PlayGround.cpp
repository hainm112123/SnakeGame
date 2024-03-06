#include <bits/stdc++.h>
#include "PlayGround.h"
#include "Snake.h"

PlayGround::PlayGround(int _width, int _height):
    width(_width), height(_height),
    squares(vector<vector<CellType>>(_height, vector<CellType>(_width, CELL_EMPTY))),
    snake(this), status(GAME_RUNNING), score(0)
{
    addCherry();
}

void PlayGround::changeCellState(Position position, CellType type) {
    squares[position.x][position.y] = type;
}

void PlayGround::processUserInput(UserInput input) {
    snake.processUserInput(input);
}

bool PlayGround::nextStep() {
    return snake.nextStep();
}

CellType PlayGround::getCellState(Position pos) {
    return squares[pos.x][pos.y];
}

void PlayGround::addCherry() {
    int w = getWidth(), h = getHeight();
    while (1) {
        Position p(rand() % h, rand() % w);
        if (getCellState(p) == CELL_EMPTY) {
            changeCellState(p, CELL_CHERRY);
            cherry = p;
            break;
        }
    }
}

void PlayGround::setGameStatus(GameStatus newStatus) {
    status = newStatus;
}

vector<Position> PlayGround::getSnakePositions() const {
    return snake.getPositions();
}
