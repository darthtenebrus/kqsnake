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
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    Snake(int, int, QBrush &);
    void drawInitial(QPainter &);
    void setDirection(Direction d);

    GameObject createNewHead();
    void removeTail();
    void move(SnakeGame &);

    [[nodiscard]]
    bool isOpposed(const Direction &, const Direction &) const;

    [[nodiscard]]
    bool checkCollision(const GameObject &);
    bool isAlive();

private:
    Direction mDir;
    QBrush mColor;
    bool mIsAlive;


};


#endif //KQSNAKE_SNAKE_H
