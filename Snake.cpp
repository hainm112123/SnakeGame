#include <bits/stdc++.h>
#include "Snake.h"
#include "PlayGround.h"

using namespace std;

SnakeNode::SnakeNode(Position p, SnakeNode *_prev, SnakeNode *_next): position(p), prev(_prev), next(_next) {}
SnakeNode* SnakeNode::addBack(Position position) {
    if (this->next == nullptr) return nullptr;
    SnakeNode *node = new SnakeNode(position, this, this->next);
    if (this->next != nullptr) this->next->prev = node;
    this->next = node;
    return node;
}
SnakeNode* SnakeNode::addFront(Position position) {
    if (this->prev == nullptr) return nullptr;
    return this->prev->addBack(position);
}
void SnakeNode::_remove() {
    if (this->next != nullptr) this->next->prev = this->prev;
    if (this->prev != nullptr) this->prev->next = this->next;
}

Position positionMove(Position pos, Direction dir) {
    return Position(pos.x + dx[dir], pos.y + dy[dir]);
}

Snake::Snake(PlayGround *_playGround): playGround(_playGround) {
    Position position((_playGround->getHeight()) / 2, (_playGround->getWidth()) / 2);
    first = new SnakeNode(Position(-1, -1)); last = new SnakeNode(Position(oo, oo));
    first->next = last; last->prev = first;
    first->addBack(position);

    playGround->changeCellState(position, CELL_SNAKE);
    direction = RIGHT;
}

void Snake::processUserInput(UserInput input) {
//    direction = changeDirection(input);
    inputQueue.push(input);
}

Direction Snake::changeDirection(UserInput input) {
    switch(input) {
        case KEY_UP:
            return direction != DOWN ? UP : direction;
        case KEY_DOWN:
            return direction != UP ? DOWN : direction;
        case KEY_LEFT:
            return direction != RIGHT ? LEFT : direction;
        case KEY_RIGHT:
            return direction != LEFT ? RIGHT : direction;
        default:
            return direction;
    }
}

void print(Position p) {
    cout << p.x << " " << p.y << "\n";
}

bool Snake::nextStep() {
    int static cherry = 0;

    while (!inputQueue.empty()) {
        UserInput input = inputQueue.front();
        inputQueue.pop();
        Direction newDirection = changeDirection(input);
        if (newDirection != direction) {
            direction = newDirection;
            break;
        }
    }

    Position newPosition = positionMove(last->prev->position, direction);
    if (!validate(newPosition)) return false;

    CellType type = playGround->getCellState(newPosition);
    if (type == CELL_CHERRY) cherry ++;

    last->addFront(newPosition);
    if (cherry > 0) {
        cherry --;
    }
    else {
        playGround->changeCellState(first->next->position, CELL_EMPTY);
        first->next->_remove();
    }
    playGround->changeCellState(newPosition, CELL_SNAKE);

    if (type == CELL_CHERRY) {
        playGround->addCherry();
    }

    return true;
}

bool Snake::validate(Position pos) {
    int w = playGround->getWidth(), h = playGround->getHeight();
    if (!(0 <= pos.x && pos.x < h && 0 <= pos.y && pos.y < w) || (playGround->getCellState(pos) == CELL_SNAKE && pos != first->next->position)) {
        playGround->setGameStatus(GAME_LOST);
        return false;
    }
    return true;
}

vector<Position> Snake::getPositions() const {
    vector< Position > res;
    for (SnakeNode *it = first->next; it != last; it = it->next) {
        res.push_back(it->position);
    }
    return res;
}
