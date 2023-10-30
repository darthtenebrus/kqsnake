//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_SNAKE_H
#define KQSNAKE_SNAKE_H


#include <QBrush>
#include <QQueue>
#include "gameobject.h"

class Snake {

public:
    Snake(int, int, QBrush &, QBrush &);
    virtual ~Snake();
    QBrush &colorize(int x, int y);

private:
    QQueue<GameObject> *mSnakeParts;

    QBrush &mEmpty;
    QBrush &mBody;
};


#endif //KQSNAKE_SNAKE_H
