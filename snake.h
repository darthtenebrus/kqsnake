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
    Snake(int, int, QBrush &);
    virtual ~Snake();
    void drawInitial(QPainter &);


private:
    QQueue<GameObject> *mSnakeParts;
};


#endif //KQSNAKE_SNAKE_H
