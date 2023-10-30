//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_SNAKE_H
#define KQSNAKE_SNAKE_H


#include <QList>
#include <QBrush>
#include "gameobject.h"

class Snake {

public:
    Snake(int, int);
    virtual ~Snake();
    QBrush colorize(int x, int y);

private:
    QList<GameObject> *mSnakeParts;
    QList<GameObject> *getParts(void);

};


#endif //KQSNAKE_SNAKE_H
