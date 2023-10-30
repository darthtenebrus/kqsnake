//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_SNAKE_H
#define KQSNAKE_SNAKE_H


#include <QList>
#include "gameobject.h"

class Snake {

public:
    Snake(int, int);
    virtual ~Snake();
    QList<GameObject> *getParts(void);

private:
    QList<GameObject> *mSnakeParts;
};


#endif //KQSNAKE_SNAKE_H
