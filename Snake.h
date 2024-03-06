#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

const int oo = int(1e9) + 10;

class PlayGround;

typedef pair<int, int> Position;

enum UserInput {
    NO_INPUT = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
};

enum Direction {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

Position positionMove(Position pos, Direction dir);

struct SnakeNode {
    Position position;
    SnakeNode *prev, *next;

    SnakeNode(Position p, SnakeNode *_prev = nullptr, SnakeNode *_next = nullptr);

    SnakeNode* addFront(Position p);
    SnakeNode* addBack(Position p);
    void _remove();
};

class Snake {
public:
    SnakeNode *first, *last;
    PlayGround *playGround;
    Direction direction;
    queue<UserInput>inputQueue;
public:
    Snake(PlayGround *_playGround);

    void processUserInput(UserInput input);
    Direction changeDirection(UserInput input);
    bool nextStep();
    bool validate(Position pos);
    vector<Position> getPositions() const;
};

#endif // SNAKE_H_INCLUDED
