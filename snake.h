//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_SNAKE_H
#define KQSNAKE_SNAKE_H


#include <QBrush>
#include <QQueue>
#include "gameobject.h"

class SnakeGame;
class Snake : public QQueue<GameObject> {


public:
    enum Direction {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT
    };
    Snake(int, int);
    void drawInitial(QPainter &);
    Direction &getDirection();

    GameObject createNewHead();
    void removeTail();
    void move(SnakeGame *);

    [[nodiscard]]
    bool checkCollision(const GameObject &);
    bool checkCollision(int, int);
    bool isAlive();

private:
    Direction mDir;
    bool mIsAlive;
    QPixmap mBody;
};

Snake::Direction & operator--(Snake::Direction &);
Snake::Direction & operator++(Snake::Direction &);

#endif //KQSNAKE_SNAKE_H
